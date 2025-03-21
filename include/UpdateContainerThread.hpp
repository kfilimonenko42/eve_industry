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

#ifndef _EVEINDUSTRY_UPDATECONTAINERTHREAD_HPP_
#define _EVEINDUSTRY_UPDATECONTAINERTHREAD_HPP_

#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <queue>
#include <utility>
#include <functional>
#include <unordered_map>
#include <chrono>

#include "ChronoTools.hpp"

namespace EVE::Industry
{

	template<typename T>
	class UpdateContainerThread
	{
	public:
		explicit UpdateContainerThread(const std::function<bool(const T& elem)>& func);
		~UpdateContainerThread() noexcept;

		UpdateContainerThread(const UpdateContainerThread&) = delete;
		UpdateContainerThread& operator=(const UpdateContainerThread&) = delete;
		UpdateContainerThread(UpdateContainerThread&&) = delete;
		UpdateContainerThread& operator=(UpdateContainerThread&&) = delete;

		void push(const T& record);
		time_point lastUpdate(int owner_id);
		time_point setLastUpdateNow(int owner_id);

	private:
		void stop() noexcept;
		void update();
		void saveTimeUpd(const T& record);

	private:
		std::thread m_Thread;
		std::mutex m_Mutex;
		std::condition_variable m_Cv;
		std::atomic<bool> m_StopUpdThread{};
		std::atomic<bool> m_PauseUpdThread{ true };
		std::queue<T> m_UpdQueue;
		std::function<bool(const T& elem)> m_UpdFunc;
		std::unordered_map<int, time_point> m_UpdTime;
	};

	template<typename T>
	inline UpdateContainerThread<T>::UpdateContainerThread(const std::function<bool(const T& elem)>& func)
		: m_Thread{ std::thread(&UpdateContainerThread::update, this) }, m_UpdFunc{ func }
	{
	}

	template<typename T>
	inline UpdateContainerThread<T>::~UpdateContainerThread() noexcept
	{
		stop();
	}

	template<typename T>
	inline void UpdateContainerThread<T>::push(const T& record)
	{
		m_UpdQueue.push(record);
		m_PauseUpdThread = false;
		m_Cv.notify_one();
	}

	template<typename T>
	inline time_point UpdateContainerThread<T>::lastUpdate(int owner_id)
	{
		if (m_UpdTime.contains(owner_id))
		{
			return m_UpdTime.at(owner_id);
		}

		return setLastUpdateNow(owner_id);
	}

	template<typename T>
	inline time_point UpdateContainerThread<T>::setLastUpdateNow(int owner_id)
	{
		const time_point now = std::chrono::high_resolution_clock::now();
		m_UpdTime[owner_id] = now;

		return now;
	}

	template<typename T>
	inline void UpdateContainerThread<T>::stop() noexcept
	{
		m_StopUpdThread = true;
		m_PauseUpdThread = true;
		m_Cv.notify_one();
		if (m_Thread.joinable())
		{
			m_Thread.join();
		}
	}

	template<typename T>
	inline void UpdateContainerThread<T>::update()
	{
		while (true)
		{
			std::unique_lock<std::mutex> ul(m_Mutex);

			m_Cv.wait(ul, [this]() { return m_StopUpdThread || !m_PauseUpdThread; });

			if (m_StopUpdThread)
			{
				break;
			}

			const T& record = m_UpdQueue.front();
			if (m_UpdFunc(record))
			{
				saveTimeUpd(record);
			}

			m_UpdQueue.pop();

			if (m_UpdQueue.empty())
			{
				m_PauseUpdThread = true;
			}
		}
	}

	template<typename T>
	inline void UpdateContainerThread<T>::saveTimeUpd(const T& record)
	{
		m_UpdTime[record.m_OwnerId] = std::chrono::high_resolution_clock::now();
	}

}

#endif // _EVEINDUSTRY_UPDATECONTAINERTHREAD_HPP_