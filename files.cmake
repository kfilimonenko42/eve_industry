#source files
set(LOGGER_src
	include/FileLogger.cpp
	include/FileLogger.hpp
	include/Logger.cpp
	include/Logger.hpp
)

set(TOOLS_src
	include/EnumTools.hpp
	include/JsonHelper.cpp
	include/JsonHelper.hpp
	include/StringFileHelper.cpp
	include/StringFileHelper.hpp
	include/StringTools.hpp
)

set(RESTAPI_src
	include/Request.cpp
	include/Request.hpp
	include/Response.hpp
)

set(ESI_src
	include/ESI.hpp
	include/ESI_certificate.hpp
)

set(GITHUBAPI_src
	include/GithubAPI.hpp
	include/GithubAPI_certificate.hpp
)

set(ASSETS_src
	include/Agent.hpp
	include/AssetContainer.hpp
	include/Blueprint.cpp
	include/Blueprint.hpp
	include/BlueprintMaterialEfficiency.hpp
	include/BlueprintSettings.hpp
	include/Category.cpp
	include/Category.hpp
	include/Constellation.hpp
	include/Group.cpp
	include/Group.hpp
	include/IBaseLoaders.hpp
	include/InventionProduct.cpp
	include/InventionProduct.hpp
	include/JsonAssetsLoader.cpp
	include/JsonAssetsLoader.hpp
	include/MarketGroup.cpp
	include/MarketGroup.hpp
	include/Material.cpp
	include/Material.hpp
	include/Order.hpp
	include/PI.hpp
	include/Point.cpp
	include/Point.hpp
	include/Region.hpp
	include/Settings.hpp
	include/SolarSystem.hpp
	include/Station.hpp
	include/Type.hpp
)

set(INDUSTRY_src
	include/Appraisal.cpp
	include/Appraisal.hpp
	include/AppraisalContainer.cpp
	include/AppraisalContainer.hpp
	include/Assets.cpp
	include/Assets.hpp
	include/BaseRecord.cpp
	include/BaseRecord.hpp
	include/BitmapContainer.cpp
	include/BitmapContainer.hpp
	include/BlueprintProject.cpp
	include/BlueprintProject.hpp
	include/BlueprintRecord.cpp
	include/BlueprintRecord.hpp
	include/DecomposeBlueprints.cpp
	include/DecomposeBlueprints.hpp
	include/EsiOrderSettings.hpp
	include/EveIndustryApp.cpp
	include/EveIndustryApp.hpp
	include/FormAddTypesText.cpp
	include/FormAddTypesText.hpp
	include/FormApplication.cpp
	include/FormApplication.hpp
	include/FormAppraisal.cpp
	include/FormAppraisal.hpp
	include/FormMaterialsStages.cpp
	include/FormMaterialsStages.hpp
	include/FormProject.cpp
	include/FormProject.hpp
	include/FormProjectName.cpp
	include/FormProjectName.hpp
	include/FormSelectBlueprintME.cpp
	include/FormSelectBlueprintME.hpp
	include/FormSelectMaxRuns.cpp
	include/FormSelectMaxRuns.hpp
	include/FormSelectRegion.cpp
	include/FormSelectRegion.hpp
	include/FormSelectRigME.cpp
	include/FormSelectRigME.hpp
	include/FormSelectSolarSystem.cpp
	include/FormSelectSolarSystem.hpp
	include/FormSelectStation.cpp
	include/FormSelectStation.hpp
	include/FormSelectStructME.cpp
	include/FormSelectStructME.hpp
	include/FormType.cpp
	include/FormType.hpp
	include/IBaseStringParser.hpp
	include/IIndustryLoader.hpp
	include/IIndustrySaver.hpp
	include/IListCtrlLayout.hpp
	include/IListInfoUpdater.hpp
	include/IndustryCalculation.cpp
	include/IndustryCalculation.hpp
	include/IndustryCalculation_Tools.hpp
	include/IndustryProject.cpp
	include/IndustryProject.hpp
	include/IndustryProject_utility.hpp
	include/JsonIndustryLoader.cpp
	include/JsonIndustryLoader.hpp
	include/JsonIndustrySaver.cpp
	include/JsonIndustrySaver.hpp
	include/ListBoxLayoutBox_Region.cpp
	include/ListBoxLayoutBox_Region.hpp
	include/ListBoxLayoutBox_SolarSystem.cpp
	include/ListBoxLayoutBox_SolarSystem.hpp
	include/ListBoxLayoutBox_Station.cpp
	include/ListBoxLayoutBox_Station.hpp
	include/ListDataWrapper.hpp
	include/ListLayout_AvailableMaterials.cpp
	include/ListLayout_AvailableMaterials.hpp
	include/ListLayout_BlueprintsProject.cpp
	include/ListLayout_BlueprintsProject.hpp
	include/ListLayout_MaterialsAppraisal.cpp
	include/ListLayout_MaterialsAppraisal.hpp
	include/ListLayout_MaterialsBase.cpp
	include/ListLayout_MaterialsBase.hpp
	include/ListLayout_MaterialsBlueprint.cpp
	include/ListLayout_MaterialsBlueprint.hpp
	include/ListLayout_MaterialsProject.cpp
	include/ListLayout_MaterialsProject.hpp
	include/ListLayout_ProductionStages.cpp
	include/ListLayout_ProductionStages.hpp
	include/ListLayout_TypeManufacturing.cpp
	include/ListLayout_TypeManufacturing.hpp
	include/ListOfRegions.cpp
	include/ListOfRegions.hpp
	include/ListOfSolarSystems.cpp
	include/ListOfSolarSystems.hpp
	include/ListOfStations.cpp
	include/ListOfStations.hpp
	include/MaterialAppraisal.cpp
	include/MaterialAppraisal.hpp
	include/MaterialBase.cpp
	include/MaterialBase.hpp
	include/MaterialBlueprint.cpp
	include/MaterialBlueprint.hpp
	include/MaterialProject.cpp
	include/MaterialProject.hpp
	include/OpenFormType.hpp
	include/ParseIndustryText.cpp
	include/ParseIndustryText.hpp
	include/ProductionStage.cpp
	include/ProductionStage.hpp
	include/ProjectNew.hpp
	include/RegionPanel.cpp
	include/RegionPanel.hpp
	include/SolarSystemPanel.cpp
	include/SolarSystemPanel.hpp
	include/SolarSystemRecord.cpp
	include/SolarSystemRecord.hpp
	include/StageStatus.hpp
	include/StationPanel.cpp
	include/StationPanel.hpp
	include/StationRecord.cpp
	include/StationRecord.hpp
	include/StringParser_v3.cpp
	include/StringParser_v3.hpp
	include/TotalValues.hpp
	include/TradeRecord.cpp
	include/TradeRecord.hpp
	include/TypeManufacturing.cpp
	include/TypeManufacturing.hpp
	include/TypePrice.cpp
	include/TypePrice.hpp
	include/TypeRecord.cpp
	include/TypeRecord.hpp
	include/VectorStrToTypeIndustry.cpp
	include/VectorStrToTypeIndustry.hpp
	include/Version.hpp
	include/wxBitmapFileSystem.hpp
	include/wxPageAvailableMaterials.cpp
	include/wxPageAvailableMaterials.hpp
	include/wxPageBlueprintsProject.cpp
	include/wxPageBlueprintsProject.hpp
	include/wxPageMaterialsBase.cpp
	include/wxPageMaterialsBase.hpp
	include/wxPageMaterialsBlueprint.cpp
	include/wxPageMaterialsBlueprint.hpp
	include/wxPageMaterialsProject.cpp
	include/wxPageMaterialsProject.hpp
	include/wxPageProductionStages.cpp
	include/wxPageProductionStages.hpp
	include/wxPageTypeDescription.cpp
	include/wxPageTypeDescription.hpp
	include/wxPageTypeHeader.cpp
	include/wxPageTypeHeader.hpp
	include/wxPageTypeIndustry.cpp
	include/wxPageTypeIndustry.hpp
	include/wxPageTypePISchema.cpp
	include/wxPageTypePISchema.hpp
	include/wxSettings.hpp
	include/WxTextToVectorStr.cpp
	include/WxTextToVectorStr.hpp
	include/wxVirtualListCtrl.hpp
)

set(ESI_src
	include/ESI.hpp
	include/ESI_certificate.hpp
)

source_group("LOGGER" FILES ${LOGGER_src})
source_group("TOOLS" FILES ${TOOLS_src})
source_group("RESTAPI" FILES ${RESTAPI_src})
source_group("ESI" FILES ${ESI_src})
source_group("GITHUBAPI" FILES ${GITHUBAPI_src})
source_group("ASSETS" FILES ${ASSETS_src})
source_group("ESI" FILES ${ESI_src})
source_group("INDUSTRY" FILES ${INDUSTRY_src})

set(SOURCE_FILES
	${LOGGER_src}
	${TOOLS_src}
	${RESTAPI_src}
	${ESI_src}
	${GITHUBAPI_src}
	${ASSETS_src}
	${ESI_src}
	${INDUSTRY_src}
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})