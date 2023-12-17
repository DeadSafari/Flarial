#pragma once
#include <string>
#include <unordered_map>

#include "../Actor/Actor.hpp"

class Actor;

class mcUUID {
public:
    uint64_t mostSig, leastSig;
};

enum PlayerListPacketType : int8_t {
	AddPlayerEntry = 0x0,  // The names are just add and removed but i dont want to cause issues
	RemovePlayerEntry = 0x1,
};

class PlayerListEntry {
public:
	uint64_t id; // This is the ActorUniqueID
	mcUUID UUID;
	std::string name, XUID, platformOnlineId;
	int buildPlatform;
	char filler[0x164];
	//SerializedSkin skin;
	bool isTeacher, isHost;
};

class Level {
public:
    char pad_0000[0x1EA8]; //0x0000
    std::unordered_map<mcUUID, PlayerListEntry> playermap; //0x1EA8

	std::vector<Actor*> getRuntimeActorList() {
		using Level_getRuntimeActorListFunc = std::vector<Actor*>(__fastcall*)(Level*);
		static Level_getRuntimeActorListFunc Level_getRuntimeActorList = reinterpret_cast<Level_getRuntimeActorListFunc>(Memory::findSig("40 53 48 83 EC 30 48 81 C1 D8 1C 00 00"));
		return Level_getRuntimeActorList(this);
	}
};