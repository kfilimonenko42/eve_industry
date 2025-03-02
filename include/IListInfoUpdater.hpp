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

#ifndef _EVEINDUSTRY_ILISTINFOUPDATER_
#define _EVEINDUSTRY_ILISTINFOUPDATER_

#include <vector>
#include <cassert>
#include <string>
#include <cstdint>
#include <utility>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <optional>
#include <functional>

#include "AppraisalContainer.hpp"
#include "BitmapContainer.hpp"
#include "EsiOrderSettings.hpp"

namespace EVE::Industry
{

	struct IListInfoUpdater
	{
		explicit IListInfoUpdater(const std::function<void()>& fAfterUpdate)
			: m_fAfterUpdate{ fAfterUpdate }
		{
		}

		virtual ~IListInfoUpdater()
		{
			join();
			m_StopThread = true;
		}

		void stop()
		{
			join();
		}

		void start(std::vector<std::uint32_t> ids)
		{
			m_StopThread = false;
			update(std::move(ids));
		}

		virtual void update(std::vector<std::uint32_t>&& ids) = 0;

	protected:
		void join()
		{
			if (m_UpdThread)
			{
				m_StopThread = true;
				if (m_UpdThread->joinable())
				{
					m_UpdThread->join();
				}
			}
		}

	protected:
		std::optional<std::thread> m_UpdThread;
		std::atomic<bool> m_StopThread{};
		std::function<void()> m_fAfterUpdate;
	};

	struct PriceUpdater : public IListInfoUpdater
	{
		explicit PriceUpdater(const std::function<void()>& mainUpd, const EsiOrderSettings& esiSettings)
			: IListInfoUpdater(mainUpd), m_EsiSettings{ esiSettings }
		{
		}

		~PriceUpdater() override = default;

		void update(std::vector<std::uint32_t>&& ids) override
		{
			m_UpdThread = std::thread(&PriceUpdater::do_update, this, std::move(ids));
		}

	private:
		void do_update(std::vector<std::uint32_t>&& ids)
		{
			AppraisalContainer& container = AppraisalContainer::Instance();

			EsiOrderSettings currentEsiSettings = m_EsiSettings;
			for (const std::uint32_t id : ids)
			{
				if (m_StopThread)
				{
					break;
				}
				container.push(id, currentEsiSettings);
			}

			if (m_fAfterUpdate && !m_StopThread)
			{
				m_fAfterUpdate();
			}
		}

	private:
		const EsiOrderSettings& m_EsiSettings;
	};

	struct ImagesUpdater : public IListInfoUpdater
	{
		explicit ImagesUpdater(const std::function<void()>& mainUpd)
			: IListInfoUpdater(mainUpd)
		{
		}

		~ImagesUpdater() override = default;

		void update(std::vector<std::uint32_t>&& ids) override
		{
			m_UpdThread = std::thread(&ImagesUpdater::do_update, this, std::move(ids));
		}

	private:
		void do_update(std::vector<std::uint32_t>&& ids)
		{
			BitmapContainer& container = BitmapContainer::Instance();

			for (const std::uint32_t id : ids)
			{
				if (m_StopThread)
				{
					break;
				}
				container.update16(id);
			}

			if (m_fAfterUpdate && !m_StopThread)
			{
				m_fAfterUpdate();
			}
		}
	};

} // EVE::Industry

#endif // _EVEINDUSTRY_ILISTINFOUPDATER_