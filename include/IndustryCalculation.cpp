/*
	EVE bulk indy
	Copyright (C) 2025 Kirill Filimonenko

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "IndustryCalculation.hpp"
#include "Assets.hpp"
#include "TypeRecord.hpp"
#include "BlueprintRecord.hpp"
#include "IndustryCalculation_Tools.hpp"

EVE::Industry::IndustryCalculation::IndustryElement::IndustryElement(
	TypeRecord&& type,
	BlueprintRecord&& blueprint,
	SolarSystemRecord&& solSystem,
	const std::uint64_t quantity,
	const std::uint64_t stock,
	const std::uint64_t maxRunsPerJob,
	EVE::Assets::BlueprintMaterialEfficiency bpME)
	: m_Type{ std::move(type) }, m_Blueprint{ std::move(blueprint) }, m_SolarSystem{ std::move(solSystem) }, m_BpME{ bpME },
	m_Quantity{ quantity }, m_Stock{ stock }, m_MaxRunsPerJob{ maxRunsPerJob }
{
	m_IsRaw = this->m_Type.bpID() == 0;

	Log::LOG_DEBUG(
		std::format("added an industry element \"{}\" (id: {}), count: {}, stock : {}; max runs per job : {}",
			this->m_Type.name(), this->m_Type.id(), this->m_Quantity, this->m_Stock, this->m_MaxRunsPerJob));
}

const EVE::Industry::TypeRecord& EVE::Industry::IndustryCalculation::IndustryElement::type() const
{
	return this->m_Type;
}

const EVE::Industry::BlueprintRecord& EVE::Industry::IndustryCalculation::IndustryElement::blueprint() const
{
	return this->m_Blueprint;
}

const EVE::Industry::SolarSystemRecord& EVE::Industry::IndustryCalculation::IndustryElement::solarSystem() const
{
	return this->m_SolarSystem;
}

bool EVE::Industry::IndustryCalculation::IndustryElement::isRaw() const
{
	return this->m_IsRaw;
}

void EVE::Industry::IndustryCalculation::IndustryElement::addManufacturingElement(std::shared_ptr<IndustryElement> e)
{
	const std::uint32_t type_id = e->m_Type.id();
	if (type_id == this->m_Type.id())
	{
		return;
	}

	auto ittr = std::find_if(std::begin(this->m_ManufacturingElements), std::end(this->m_ManufacturingElements),
		[type_id](const std::shared_ptr<IndustryElement> m) 
		{
			return m->type().id() == type_id;
		});

	if (ittr == std::end(this->m_ManufacturingElements))
	{
		this->m_ManufacturingElements.push_back(e);

		Log::LOG_DEBUG(
			std::format("for type \"{}\" (id: {}) added a manufacturing element \"{}\" (id: {})",
				this->m_Type.name(), this->m_Type.id(), e->m_Type.name(), e->m_Type.id()));
	}
}

void EVE::Industry::IndustryCalculation::IndustryElement::addParentElement(std::shared_ptr<IndustryElement> e)
{
	const std::uint32_t type_id = e->m_Type.id();
	if (type_id == this->m_Type.id())
	{
		return;
	}

	auto ittr = std::find_if(std::begin(this->m_ParentElements), std::end(this->m_ParentElements),
		[type_id](const std::shared_ptr<IndustryElement> m)
		{
			return m->type().id() == type_id;
		});

	if (ittr == std::end(this->m_ParentElements))
	{
		this->m_ParentElements.push_back(e);

		Log::LOG_DEBUG(
			std::format("for type \"{}\" (id: {}) added a parent element \"{}\" (id: {})",
				this->m_Type.name(), this->m_Type.id(), e->m_Type.name(), e->m_Type.id()));
	}
}

void EVE::Industry::IndustryCalculation::IndustryElement::updateQuantity()
{
	const std::uint64_t oldQuantity = this->m_Quantity;
	this->m_Quantity = 0;
	//
	std::uint64_t stock = this->m_Stock;
	this->m_StockAfterCalculation = 0;
	this->m_ProducedStock = 0;
	//
	this->m_NeedUpdate = false;

	if (this->m_ParentElements.empty())
	{
		return;
	}

	std::uint64_t _tmpquantity{};
	for (const auto& parent : this->m_ParentElements)
	{
		if (parent->m_Blueprint.id() == 0)
		{
			continue;
		}

		const std::uint64_t _quantityOneRun = parent->quantityManufacturedMaterials(this->m_Type.id());
		const std::uint64_t _quantityParent = parent->quantity();
		const std::vector<std::uint64_t> _stagesParent = parent->getStages();

		for (const std::uint64_t run : _stagesParent)
		{
			std::uint64_t quantityComputed = EVE::Industry::quantity(
				run, _quantityOneRun, parent->m_Blueprint.isReaction(), parent->m_SolarSystem.security(),
				parent->m_BpME.m_BpME, parent->m_BpME.m_StructME, parent->m_BpME.m_RigME);

			EVE::Industry::useStock(quantityComputed, stock);
			std::uint64_t quantityProducedStock = useStock(quantityComputed, this->m_ProducedStock);

			if (this->m_Blueprint.id() != 0)
			{
				const std::uint64_t _quanManProd = this->m_Blueprint.quantityManufacturedProduct();
				if (_quanManProd > 0)
				{
					const std::uint64_t _tmp_runs = (std::uint64_t)std::ceil((double)quantityComputed / (double)_quanManProd);
					const std::uint64_t _produced_stock = (_tmp_runs * _quanManProd) - quantityComputed;
					if (_produced_stock > 0)
					{
						this->m_ProducedStock += _produced_stock;
					}
				}
			}

			_tmpquantity += quantityComputed + quantityProducedStock;
		}
	}

	this->m_Quantity = _tmpquantity;
	this->m_StockAfterCalculation = stock;

	Log::LOG_DEBUG(
		std::format("quantity updated \"{}\" (id: {}); before: {}, after: {}",
			this->m_Type.name(), this->m_Type.id(), oldQuantity, this->m_Quantity));

	updateStages();

	if (oldQuantity != this->m_Quantity)
	{
		for (auto& child : this->m_ManufacturingElements)
		{
			child->setNeedUpdate();
		}
	}
}

void EVE::Industry::IndustryCalculation::IndustryElement::updateStages()
{
	this->m_Stages.clear();

	if (this->m_Blueprint.id() == 0)
	{
		return;
	}

	if ((this->m_Quantity == 0) || (this->m_StockAfterCalculation >= this->m_Quantity))
	{
		return;
	}

	const std::uint64_t quantityNeed = this->m_Quantity - this->m_StockAfterCalculation;
	std::uint64_t runs = this->m_Blueprint.runs(quantityNeed);


	while (runs > 0)
	{
		const std::uint64_t stage_runs = (runs > this->m_MaxRunsPerJob) ? this->m_MaxRunsPerJob : runs;
		this->m_Stages.push_back(stage_runs);
		runs -= stage_runs;
	}

	std::sort(std::begin(this->m_Stages), std::end(this->m_Stages), std::greater());

	Log::LOG_DEBUG(
		std::format("stages updated \"{}\" (id: {})",
			this->m_Type.name(), this->m_Type.id()));
}

void EVE::Industry::IndustryCalculation::IndustryElement::setNeedUpdate()
{
	m_NeedUpdate = true;

	Log::LOG_DEBUG(
		std::format("set need update \"{}\" (id: {})",
			this->m_Type.name(), this->m_Type.id()));
}

bool EVE::Industry::IndustryCalculation::IndustryElement::getNeedUpdate() const
{
	return m_NeedUpdate;
}

void EVE::Industry::IndustryCalculation::IndustryElement::updateWeight()
{
	this->m_Weight = 0;

	if (this->m_IsRaw)
	{
		this->m_Weight = 1;
	}
	else
	{
		if (!this->m_ManufacturingElements.empty())
		{
			this->m_Weight = this->m_Blueprint.weight();
		}
	}

	Log::LOG_DEBUG(
		std::format("set weight: {}; for \"{}\" (id: {})",
			this->m_Weight, this->m_Type.name(), this->m_Type.id()));
}

std::uint64_t EVE::Industry::IndustryCalculation::IndustryElement::getWeight() const
{
	return this->m_Weight;
}

bool EVE::Industry::IndustryCalculation::IndustryElement::hasParents() const
{
	return !this->m_ParentElements.empty();
}

const std::vector<std::shared_ptr<EVE::Industry::IndustryCalculation::IndustryElement>>& EVE::Industry::IndustryCalculation::IndustryElement::getParents() const
{
	return this->m_ParentElements;
}

std::uint64_t EVE::Industry::IndustryCalculation::IndustryElement::quantity() const
{
	return this->m_Quantity;
}

std::uint64_t EVE::Industry::IndustryCalculation::IndustryElement::quantityManufacturedMaterials(std::uint64_t type_id) const
{
	if (this->m_Blueprint.id() != 0)
	{
		return this->m_Blueprint.quantityManufacturedMaterials(type_id);
	}

	return 0;
}

void EVE::Industry::IndustryCalculation::IndustryElement::clear()
{
	this->m_ManufacturingElements.clear();
	this->m_ParentElements.clear();
}

const std::vector<std::uint64_t>& EVE::Industry::IndustryCalculation::IndustryElement::getStages() const
{
	return this->m_Stages;
}

EVE::Industry::IndustryCalculation::IndustryCalculation(const EVE::Industry::IndustryProject& project, const bool fullCalculation)
	: m_FullCalculation{ fullCalculation }
{
	if (!project.m_BlueprintsList.empty())
	{
		setIndustryElements(project);
		updateWeights();
		calculate(project);
	}
}

EVE::Industry::IndustryCalculation::~IndustryCalculation()
{
	clear();
}

void EVE::Industry::IndustryCalculation::clear()
{
	for (auto elem : m_IndustryElements)
	{
		elem->clear();
	}

	this->m_IndustryElements.clear();
}

void EVE::Industry::IndustryCalculation::getRawMaterials(std::vector<MaterialBase>& raw)
{
	raw.clear();

	auto filter = std::views::filter(
		[](const std::shared_ptr<IndustryElement>& elem)
		{
			return elem->isRaw();
		});

	auto filteredElements = this->m_IndustryElements | filter;
	if (filteredElements.empty())
	{
		return;
	}

	for (auto elem : filteredElements)
	{
		try
		{
			raw.emplace_back(TypeRecord{ elem->type() }, elem->quantity());
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}
}

void EVE::Industry::IndustryCalculation::getBpsMaterials(std::vector<MaterialBlueprint>& types)
{
	types.clear();

	auto filter = std::views::filter(
		[](const std::shared_ptr<IndustryElement>& elem)
		{
			return !elem->isRaw();
		});

	auto filteredElements = this->m_IndustryElements | filter;
	if (filteredElements.empty())
	{
		return;
	}

	for (auto elem : filteredElements)
	{
		try
		{
			types.emplace_back(elem->blueprint(), elem->type(), elem->quantity());
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}
}

void EVE::Industry::IndustryCalculation::getAllMaterials(std::vector<MaterialProject>& materials)
{
	materials.clear();

	for (auto elem : this->m_IndustryElements)
	{
		try
		{
			materials.emplace_back(TypeRecord{ elem->type() }, elem->quantity());
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}
}

void EVE::Industry::IndustryCalculation::getAllMaterialsNoIndustryMaterials(std::vector<MaterialProject>& materials)
{
	materials.clear();

	auto filter = std::views::filter(
		[](const std::shared_ptr<IndustryElement>& elem)
		{
			return elem->hasParents();
		});

	auto filteredElements = this->m_IndustryElements | filter;
	if (filteredElements.empty())
	{
		return;
	}

	for (auto elem : filteredElements)
	{
		try
		{
			materials.emplace_back(TypeRecord{ elem->type() }, elem->quantity());
		}
		catch (const std::runtime_error& er)
		{
			Log::LOG_ERROR(er.what());
		}
	}
}

void EVE::Industry::IndustryCalculation::getStages(std::vector<ProductionStage>& stages)
{
	stages.clear();
	if (m_IndustryElements.empty())
	{
		return;
	}

	std::sort(std::begin(this->m_IndustryElements), std::end(this->m_IndustryElements), 
		[](const std::shared_ptr<IndustryElement>& lhs, const std::shared_ptr<IndustryElement>& rhs)
		{
			return lhs->getWeight() < rhs->getWeight();
		});

	std::uint32_t _stage{};
	for (const auto& elem : this->m_IndustryElements)
	{
		if (elem->isRaw())
		{
			continue;
		}

		for (auto run : elem->getStages())
		{
			try
			{
				stages.emplace_back(_stage, elem->blueprint(), elem->solarSystem(), run);
			}
			catch (const std::runtime_error& er)
			{
				Log::LOG_ERROR(er.what());
			}
			++_stage;
		}
	}
}

void EVE::Industry::IndustryCalculation::setIndustryElements(const EVE::Industry::IndustryProject& project)
{
	std::set<std::uint32_t> projectTypes;

	for (const auto& type : project.m_TypesProject.get())
	{
		const std::uint32_t type_id = type.m_Type.id();
		projectTypes.insert(type_id);

		const auto bpProject = getBlueprintProjectFromIndustryType(project.m_BlueprintsList.get(), type_id);
		const std::uint64_t stock = project.getStock(type_id);

		if (bpProject)
		{
			TypeRecord tmp_type = type.m_Type;
			BlueprintRecord tmp_bp = bpProject->m_Blueprint;
			SolarSystemRecord tmp_ss = bpProject->m_SolarSystem;
			addIndustryElement(std::move(tmp_type), std::move(tmp_bp), std::move(tmp_ss), type.m_Type.getQuantity(), stock,
				bpProject->m_MaxRunsPerJob, bpProject->m_ME);
		}
	}

	updateStages();

	while (!m_FillQueue.empty())
	{
		auto parent = this->m_FillQueue.front();
		const bool setNeedUpdate = projectTypes.contains(parent->type().id());

		const BlueprintRecord bp = parent->blueprint();
		if (bp.id() != 0)
		{
			for (const EVE::Assets::Material& material : bp.getManufacturingMaterials())
			{
				const std::uint32_t type_id = material.type_id();
				
				TypeRecord type;
				try
				{
					type = TypeRecord{type_id};
				}
				catch (const std::runtime_error& er)
				{
					Log::LOG_ERROR(er.what());
					continue;
				}

				const auto bpProject = getBlueprintProjectFromIndustryType(project.m_BlueprintsList.get(), type.id());
				BlueprintRecord blueprint = bpProject ? bpProject->m_Blueprint : BlueprintRecord{};
				SolarSystemRecord tmp_ss = bpProject ? bpProject->m_SolarSystem : SolarSystemRecord{};
				const std::uint64_t stock = project.getStock(type_id);
				const std::uint64_t maxRunsPerJob = bpProject ? bpProject->m_MaxRunsPerJob: 0;
				const EVE::Assets::BlueprintMaterialEfficiency me = bpProject ? bpProject->m_ME : EVE::Assets::BlueprintMaterialEfficiency{};

				addIndustryElement(std::move(type), std::move(blueprint), std::move(tmp_ss), 0, stock, maxRunsPerJob, me, setNeedUpdate, parent);
			}
		}

		this->m_FillQueue.pop();
	}
}

void EVE::Industry::IndustryCalculation::calculate(const EVE::Industry::IndustryProject& project)
{
	std::size_t stage{};

	std::sort(std::begin(this->m_IndustryElements), std::end(this->m_IndustryElements),
		[](const std::shared_ptr<IndustryElement>& lhs, const std::shared_ptr<IndustryElement>& rhs)
		{
			return lhs->getWeight() > rhs->getWeight();
		});

	while (true)
	{
		auto filter = std::views::filter(
			[](const std::shared_ptr<IndustryElement>& elem)
			{
				return elem->getNeedUpdate();
			});

		auto filteredElements = this->m_IndustryElements | filter;
		if (filteredElements.empty())
		{
			break;
		}

		for (auto elem : filteredElements)
		{
			elem->updateQuantity();
		}

		++stage;

#if _DEBUG
		if (stage > 1000)
		{
			Log::LOG_DEBUG("calculation was stopped (more 1000 stages)");
			break;
		}
#endif
	}

	Log::LOG_DEBUG(
		std::format("calculation was finished in {} stages", stage));
}

void EVE::Industry::IndustryCalculation::addIndustryElement(
	TypeRecord&& type,
	BlueprintRecord&& blueprint,
	SolarSystemRecord&& solSystem,
	const std::uint64_t quantity,
	const std::uint64_t stock,
	const std::uint64_t maxRunsPerJob,
	const EVE::Assets::BlueprintMaterialEfficiency bpME,
	const bool needUpdate,
	std::shared_ptr<IndustryElement> parent)
{
	const std::uint32_t type_id = type.id();
	auto ittr = std::find_if(std::begin(this->m_IndustryElements), std::end(this->m_IndustryElements),
		[type_id](const std::shared_ptr<IndustryElement>& m)
		{
			return m->type().id() == type_id;
		});

	if (ittr != std::end(this->m_IndustryElements))
	{
		makeLinkParentChild(parent, (*ittr));
		return;
	}

	auto element = this->m_IndustryElements.emplace_back(
		std::make_shared<IndustryElement>(
			std::move(type),
			std::move(blueprint),
			std::move(solSystem),
			quantity,
			stock,
			maxRunsPerJob,
			bpME));

	makeLinkParentChild(parent, element);

	if (needUpdate)
	{
		element->setNeedUpdate();
	}

	if (element->isRaw())
	{
		return;
	}

	if (element->hasParents() && !this->m_FullCalculation)
	{
		return;
	}

	this->m_FillQueue.push(element);
}

void EVE::Industry::IndustryCalculation::makeLinkParentChild(
	std::shared_ptr<IndustryElement> parent, std::shared_ptr<IndustryElement> child)
{
	if (parent && child)
	{
		parent->addManufacturingElement(child);
		child->addParentElement(parent);
	}
}

void EVE::Industry::IndustryCalculation::updateWeights()
{
	std::for_each(std::begin(m_IndustryElements), std::end(m_IndustryElements),
		[](std::shared_ptr<IndustryElement> elem)
		{
			elem->updateWeight();
		});
}

void EVE::Industry::IndustryCalculation::updateStages()
{
	for (auto& element : this->m_IndustryElements)
	{
		element->updateStages();
	}
}
