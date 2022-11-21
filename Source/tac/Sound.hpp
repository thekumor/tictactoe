#pragma once

#include <sfml/audio.hpp>
#include <string>
#include <unordered_map>
#include <memory>

namespace tac {

	class SoundBuffer
	{
	public:
		friend class Sound;

		SoundBuffer(const std::string& path);
		SoundBuffer() = default;

		bool Load(const std::string& path);

	private:
		sf::SoundBuffer m_Buffer;
		std::string m_Path = "";
	};

	class Sound
	{
	public:
		Sound(const std::string& path);
		Sound() = default;

		void Play();
		bool Load(const std::string& path);

	private:
		SoundBuffer m_Buffer;
		sf::Sound m_Sound;
		std::string m_Path = "";
	};

	class SoundManager
	{
	public:
		SoundManager() = default;

		std::shared_ptr<Sound> GetSound(const std::string& path);

	private:
		std::unordered_map<std::string, std::shared_ptr<Sound>> m_Sounds = {};
	};

}