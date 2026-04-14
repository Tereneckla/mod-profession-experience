/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "Chat.h"
#include "Config.h"
#include "ConfigValueCache.h"
#include "Player.h"
#include "ScriptMgr.h"

enum class PEConfig
{
    ALCHEMY_EXPERIENCE,
    BLACKSMITH_EXPERIENCE,
    COOKING_EXPERIENCE,
    DISENCHANTING_EXPERIENCE,
    ENCHANTING_EXPERIENCE,
    ENGINEERING_EXPERIENCE,
    FISHING_EXPERIENCE,
    FIRST_AID_EXPERIENCE,
    HERBALISM_EXPERIENCE,
    INSCRIPTION_EXPERIENCE,
    JEWELCRAFTING_EXPERIENCE,
    LEATHERWORKING_EXPERIENCE,
    LOCKPICK_EXPERIENCE,
    MINING_EXPERIENCE,
    SKINNING_EXPERIENCE,
    SMELTING_EXPERIENCE,
    TAILORING_EXPERIENCE,
    MULT_GRAY,
    MULT_GREEN,
    MULT_YELLOW,
    MULT_ORANGE,
    MULT_APPRENTICE,
    MULT_JOURNEYMAN,
    MULT_EXPERT,
    MULT_ARTISAN,
    MULT_MASTER,
    MULT_GRANDMASTER,
    MULT_CURVE,

    NUM_CONFIGS,
};

class PEConfigData : public ConfigValueCache<PEConfig>
{
public:
    PEConfigData() : ConfigValueCache(PEConfig::NUM_CONFIGS) { };

    void BuildConfigCache() override
    {
        SetConfigValue<float>(PEConfig::ALCHEMY_EXPERIENCE,        "ProfessionExperience.Alchemy.Experience",        0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::BLACKSMITH_EXPERIENCE,     "ProfessionExperience.Blacksmith.Experience",     0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::COOKING_EXPERIENCE,        "ProfessionExperience.Cooking.Experience",        0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::DISENCHANTING_EXPERIENCE,  "ProfessionExperience.Disenchanting.Experience",  0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::ENCHANTING_EXPERIENCE,     "ProfessionExperience.Enchanting.Experience",     0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::ENGINEERING_EXPERIENCE,    "ProfessionExperience.Engineering.Experience",    0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::FISHING_EXPERIENCE,        "ProfessionExperience.Fishing.Experience",        0.01f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::FIRST_AID_EXPERIENCE,      "ProfessionExperience.FirstAid.Experience",       0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::HERBALISM_EXPERIENCE,      "ProfessionExperience.Herbalism.Experience",      0.01f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::INSCRIPTION_EXPERIENCE,    "ProfessionExperience.Inscription.Experience",    0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::JEWELCRAFTING_EXPERIENCE,  "ProfessionExperience.Jewelcrafting.Experience",  0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::LEATHERWORKING_EXPERIENCE, "ProfessionExperience.Leatherworking.Experience", 0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::LOCKPICK_EXPERIENCE,       "ProfessionExperience.Lockpick.Experience",       0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MINING_EXPERIENCE,         "ProfessionExperience.Mining.Experience",         0.01f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::SKINNING_EXPERIENCE,       "ProfessionExperience.Skinning.Experience",       0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::SMELTING_EXPERIENCE,       "ProfessionExperience.Smelting.Experience",       0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::TAILORING_EXPERIENCE,      "ProfessionExperience.Tailoring.Experience",      0.00f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");

        SetConfigValue<float>(PEConfig::MULT_GRAY,   "ProfessionExperience.MultGray",   0.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_GREEN,  "ProfessionExperience.MultGreen",  0.75f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_YELLOW, "ProfessionExperience.MultYellow", 1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_ORANGE, "ProfessionExperience.MultOrange", 1.25f, ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");

        SetConfigValue<float>(PEConfig::MULT_APPRENTICE, "ProfessionExperience.MultApprentice", 1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_JOURNEYMAN, "ProfessionExperience.MultJourneyman", 1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_EXPERT,     "ProfessionExperience.MultExpert",     1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_ARTISAN,    "ProfessionExperience.MultArtisan",    1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_MASTER,     "ProfessionExperience.MultMaster",     1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_GRANDMASTER,"ProfessionExperience.MultGrandMaster",1.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");
        SetConfigValue<float>(PEConfig::MULT_CURVE,      "ProfessionExperience.MultCurve",      5.0f,  ConfigValueCache::Reloadable::Yes, [](float const& value) { return value >= 0.0f; }, ">= 0");

    }
};
static PEConfigData peConfigData;

class RewardExperienceScript : public PlayerScript
{
public:
RewardExperienceScript() : PlayerScript("RewardExperienceScript", {
        PLAYERHOOK_ON_UPDATE_CRAFTING_SKILL,
        PLAYERHOOK_ON_UPDATE_GATHERING_SKILL,
        PLAYERHOOK_ON_UPDATE_FISHING_SKILL,
     }) { }

    bool OnPlayerUpdateFishingSkill(Player* player, int32 skill, int32 zone_skill, int32 /*chance*/, int32 /*roll*/) override
    {
        if (zone_skill < 1)
            zone_skill = 1;

        if (float xpFactor = peConfigData.GetConfigValue<float>(PEConfig::FISHING_EXPERIENCE))
            RewardXP(player, skill, zone_skill + 100, zone_skill + 50, zone_skill + 25, zone_skill, xpFactor);

        return true;
    }

    void OnPlayerUpdateGatheringSkill(Player* player, uint32 skillId, uint32 currentLevel, uint32 gray, uint32 green, uint32 yellow, uint32& /*gain*/) override
    {
        PEConfig experienceSetting;
        switch (skillId)
        {
            case SKILL_HERBALISM:
                experienceSetting = PEConfig::HERBALISM_EXPERIENCE;
                break;
            case SKILL_MINING:
                experienceSetting = PEConfig::MINING_EXPERIENCE;
                break;
            case SKILL_SKINNING:
                experienceSetting = PEConfig::SKINNING_EXPERIENCE;
                break;
            case SKILL_LOCKPICKING:
                experienceSetting = PEConfig::LOCKPICK_EXPERIENCE;
                break;
            default:
                return;
        }

        if (float xpFactor = peConfigData.GetConfigValue<float>(experienceSetting))
            RewardXP(player, currentLevel, gray, green, yellow, yellow - 25, xpFactor);
    }

    void OnPlayerUpdateCraftingSkill(Player *player, SkillLineAbilityEntry const* skill, uint32 currentLevel, uint32& /*gain*/) override
    {
        PEConfig experienceSetting;
        switch (skill->SkillLine)
        {
            case SKILL_ALCHEMY:
                experienceSetting = PEConfig::ALCHEMY_EXPERIENCE;
                break;
            case SKILL_BLACKSMITHING:
                experienceSetting = PEConfig::BLACKSMITH_EXPERIENCE;
                break;
            case SKILL_COOKING:
                experienceSetting = PEConfig::COOKING_EXPERIENCE;
                break;
            case SKILL_ENCHANTING:
                if (skill->Spell == 13262)
                    experienceSetting = PEConfig::DISENCHANTING_EXPERIENCE;
                else
                    experienceSetting = PEConfig::ENCHANTING_EXPERIENCE;
                break;
            case SKILL_ENGINEERING:
                experienceSetting = PEConfig::ENGINEERING_EXPERIENCE;
                break;
            case SKILL_FIRST_AID:
                experienceSetting = PEConfig::FIRST_AID_EXPERIENCE;
                break;
            case SKILL_INSCRIPTION:
                experienceSetting = PEConfig::INSCRIPTION_EXPERIENCE;
                break;
            case SKILL_JEWELCRAFTING:
                experienceSetting = PEConfig::JEWELCRAFTING_EXPERIENCE;
                break;
            case SKILL_LEATHERWORKING:
                experienceSetting = PEConfig::LEATHERWORKING_EXPERIENCE;
                break;
            case SKILL_MINING:
                experienceSetting = PEConfig::SMELTING_EXPERIENCE;
                break;
            case SKILL_TAILORING:
                experienceSetting = PEConfig::TAILORING_EXPERIENCE;
                break;
            default:
                return;
        }
        if (float xpFactor = peConfigData.GetConfigValue<float>(experienceSetting))
        {
            uint32 gray = skill->TrivialSkillLineRankHigh;
            uint32 green = (skill->TrivialSkillLineRankHigh + skill->TrivialSkillLineRankLow) / 2;
            uint32 yellow = skill->TrivialSkillLineRankLow;
            uint32 min = skill->MinSkillLineRank;
            RewardXP(player, currentLevel, gray, green, yellow, min, xpFactor);
        }
    }

    void RewardXP(Player* player, uint32 currentLevel, uint32 gray, uint32 green, uint32 yellow, uint32 minSkill, float xpFraction)
    {
        uint32 xp = player->GetUInt32Value(PLAYER_NEXT_LEVEL_XP) * xpFraction;
        if (currentLevel >= gray)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_GRAY);
        else if (currentLevel >= green)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_GREEN);
        else if (currentLevel >= yellow)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_YELLOW);
        else
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_ORANGE);
        
        if (minSkill > 375)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_GRANDMASTER);
        else if (minSkill > 300)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_MASTER);
        else if (minSkill > 225)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_ARTISAN);
        else if (minSkill > 150)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_EXPERT);
        else if (minSkill > 75)
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_JOURNEYMAN);
        else
            xp = xp * peConfigData.GetConfigValue<float>(PEConfig::MULT_APPRENTICE);
        
        if (float curve = peConfigData.GetConfigValue<float>(PEConfig::MULT_CURVE))
            xp = xp * pow(curve,(minSkill/450));
        
        player->GiveXP(xp, nullptr);
    }
};

class LoadPEConfigScript : public WorldScript
{
public:
LoadPEConfigScript() : WorldScript("LoadPEConfigScript", {
        WORLDHOOK_ON_BEFORE_CONFIG_LOAD
    }) { }

    void OnBeforeConfigLoad(bool reload) override
    {
        peConfigData.Initialize(reload);
    }
};

// Add all scripts in one
void AddProfessionExpScripts()
{
    new RewardExperienceScript();
    new LoadPEConfigScript();
}
