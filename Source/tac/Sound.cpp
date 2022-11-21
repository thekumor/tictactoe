#include "Sound.hpp"

namespace tac {

	Sound::Sound(const std::string& path)
		: m_Path(path)
	{
		Load(path);
		Play();
	}

	void Sound::Play()
	{
		m_Sound.play();
	}

	bool Sound::Load(const std::string& path)
	{
		bool loaded = m_Buffer.Load(path);
		m_Sound.setBuffer(m_Buffer.m_Buffer);

		return loaded;
	}

	SoundBuffer::SoundBuffer(const std::string& path)
		: m_Path(path)
	{
		Load(path);
	}

	bool SoundBuffer::Load(const std::string& path)
	{
		m_Path = path;

		if (!m_Buffer.loadFromFile(path))
		{
			// Error maybe?
			return false;
		}

		return true;
	}

	std::shared_ptr<tac::Sound> SoundManager::GetSound(const std::string& path)
	{
		if (m_Sounds.find(path) == m_Sounds.end())
		{
			m_Sounds[path] = std::make_shared<Sound>();
			auto& sound = m_Sounds[path];
			if (!sound->Load(path))
			{
				m_Sounds.erase(path);
				return nullptr;
			}

			return sound;
		}

		return m_Sounds[path];
	}

}