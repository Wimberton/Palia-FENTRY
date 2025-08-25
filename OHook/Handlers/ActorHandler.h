#pragma once

#include <queue>
#include <map>
#include <tuple>
#include <SDK.hpp>
#include <mutex>

enum class EType : uint32_t {
    Unknown,
    Tree = 1 << 0,
    Ore = 1 << 1,
    Bug = 1 << 2,
    Animal = 1 << 3,
    Forage = 1 << 4,
    Fish = 1 << 5,
    Loot = 1 << 6,
    Players = 1 << 7,
    NPCs = 1 << 8,
    Quest = 1 << 9,
    RummagePiles = 1 << 10,
    Stables = 1 << 11,
    Gates = 1 << 12,
    Treasure = 1 << 13,
    TimedDrop = 1 << 14,
    Relic = 1 << 15,
    Garden = 1 << 16,
    Pool = 1 << 17,
    Other = 1 << 18,
    Shops = 1 << 19,
    Bubble = 1 << 20,
    Breakable = 1 << 21,
    MAX = 1 << 22,
    MoveablePawn = Bug | Animal | Fish | Players | NPCs | Garden | Bubble,
    Despawnable = Ore | Forage,
};
UE_ENUM_OPERATORS(EType)

class FEntry {
public:
    SDK::AActor* Actor;
    SDK::FVector WorldPosition;
    std::wstring DisplayName;
    double Distance;
    double Despawn;
    FEntry(SDK::AActor* A, SDK::FVector B, std::wstring C, double D, double E) : Actor(A),WorldPosition(B),DisplayName(C),Distance(D),Despawn(E) {}
    FEntry(SDK::AActor* A) : Actor(A) {
        WorldPosition = SDK::FVector{};
        DisplayName = L"";
        Distance = 0.0;
        Despawn = 0.0;
    }
    virtual EType ActorType() = 0;
    virtual uint8_t Type() = 0;
    virtual void setType(uint8_t) = 0;
    virtual uint8_t Quality() = 0;
    virtual void setQuality(uint8_t) = 0;
    virtual uint8_t Variant() = 0;
    virtual void setVariant(uint8_t) = 0;
    virtual std::string TexturePath() = 0;
    virtual void setTexturePath(std::string) = 0;
    virtual bool Infected() = 0;
    virtual void setInfected(bool) = 0;
    bool ShouldShow(const SDK::AValeriaCharacter*);

    virtual ~FEntry() {}
};

class FEntryBackwardsCompat : public FEntry {
public:
    FEntryBackwardsCompat(SDK::AActor* A, SDK::FVector B, std::wstring C, EType D, uint8_t E, uint8_t F, uint8_t G, double H, std::string I, double J) : FEntry(A,B,C,H,J),ActorTypeInt(D),TypeInt(E),QualityInt(F),VariantInt(G),TexturePathInt(I),InfectedInt(false) {}
private:
    EType ActorTypeInt;
    uint8_t TypeInt;
    uint8_t QualityInt;
    uint8_t VariantInt;
    std::string TexturePathInt;
    bool InfectedInt;
public:
    EType ActorType() { return ActorTypeInt; }
    uint8_t Type() { return TypeInt; }
    void setType(uint8_t x) {TypeInt = x; }
    uint8_t Quality() { return QualityInt; }
    void setQuality(uint8_t x) { QualityInt = x; }
    uint8_t Variant() { return VariantInt; }
    void setVariant(uint8_t x) { VariantInt = x; }
    std::string TexturePath() { return TexturePathInt; }
    void setTexturePath(std::string x) { TexturePathInt = x; }
    bool Infected() {return InfectedInt; }
    void setInfected(bool isInfected) { InfectedInt = isInfected; }
};

class FEntryLumber : public FEntry {
public:
    FEntryLumber(SDK::AActor* A, std::string ClassName) : FEntry(A) {
        TypeInt = TypeEnum::Unknown;
        VariantInt = VariantEnum::Unknown;
        QualityInt = 0;
        InfectedInt = false;
        Flow = false;
        Name = L"";

        if (ClassName.find("Birch") != std::string::npos) {
            Name = L"Birch";
            TypeInt = TypeEnum::Sapwood;
        } else if (ClassName.find("Bush") != std::string::npos) {
            Name = L"Bush";
            TypeInt = TypeEnum::Bush;
            VariantInt = VariantEnum::Sapling;
        } else if (ClassName.find("Elder") != std::string::npos) {
            Name = L"Ancient";
            TypeInt = TypeEnum::Ancientwood;
        } else if (ClassName.find("Juniper") != std::string::npos) {
            Name = L"Juniper";
            TypeInt = TypeEnum::Sapwood;
        } else if (ClassName.find("Oak") != std::string::npos) {
            Name = L"Oak";
            TypeInt = TypeEnum::Sapwood;
        } else if (ClassName.find("Pine") != std::string::npos) {
            Name = L"Pine";
            TypeInt = TypeEnum::Heartwood;
        }

        if (ClassName.find("Sapling") != std::string::npos) {
            Name += L" XS";
            VariantInt = VariantEnum::Sapling;
        } else if (ClassName.find("Small") != std::string::npos) {
            Name += L" S";
            VariantInt = VariantEnum::Small;
        } else if (ClassName.find("Medium") != std::string::npos) {
            Name += L" M";
            VariantInt = VariantEnum::Medium;
        } else if (ClassName.find("Large") != std::string::npos) {
            Name += L" L";
            VariantInt = VariantEnum::Large;
        }

        DisplayName = Name;
    }

    enum class TypeEnum : uint8_t {
        Unknown,
        Flow,
        Heartwood,
        Sapwood,
        Bush,
        Ancientwood,
        Infected,
        MAX
    };
    static inline std::vector<std::string> TypeString = {
        "Unknown",
        "Flow",
        "Heartwood",
        "Sapwood",
        "Bush",
        "Ancientwood",
        "Infected"
    };

    enum class VariantEnum : uint8_t {
        Unknown,
        Sapling,
        Small,
        Medium,
        Large,
        MAX
    };
    static inline std::vector<std::string> VariantString = {
        "Unknown",
        "Sapling",
        "Small",
        "Medium",
        "Large",
    };

private:
    TypeEnum TypeInt;
    VariantEnum VariantInt;
    uint8_t QualityInt;
    bool Flow;
    bool InfectedInt;
    std::wstring Name;

    static inline std::string Textures[static_cast<int>(TypeEnum::MAX)] = {
        "", // Unknown
        "/Game/UI/Icons/Icon_Wood_Magicwood.Icon_Wood_Magicwood", // Flow
        "/Game/UI/Icons/Icon_Wood_Hardwood.Icon_Wood_Hardwood", // Heartwood
        "/Game/UI/Icons/Icon_Wood_Softwood.Icon_Wood_Softwood", // Sapwood
        "/Game/UI/Icons/Icon_Plant_Fiber.Icon_Plant_Fiber", // Bush
        "/Game/UI/Icons/Icon_Wood_Elderwoodwood.Icon_Wood_Elderwoodwood", // Elderwood
    };
public:
    EType ActorType() { return EType::Tree; }
    uint8_t Type() { 
        if (Flow) {
            return static_cast<uint8_t>(TypeEnum::Flow);
        } else if (InfectedInt) {
            return static_cast<uint8_t>(TypeEnum::Infected);
        }
        return static_cast<uint8_t>(TypeInt);
    }
    void setType(uint8_t x) {}
    uint8_t Quality() { return QualityInt; }
    void setQuality(uint8_t x) {
        if (x == 1) {
            Flow = true;
            DisplayName = L"Flow-Infused " + Name;
        }
    }
    uint8_t Variant() { return static_cast<uint8_t>(VariantInt); }
    void setVariant(uint8_t x) {}
    std::string TexturePath() {
        if (Flow) {
            return Textures[1];
        }
        return Textures[static_cast<int>(TypeInt)];
    }
    void setTexturePath(std::string x) {}
    bool Infected() {return InfectedInt; }
    void setInfected(bool isInfected) {InfectedInt = isInfected; }
};

class FEntryMining : public FEntry {
public:
    FEntryMining(SDK::AActor* A, std::string ClassName) : FEntry(A) {
        TypeInt = TypeEnum::Unknown;
        VariantInt = VariantEnum::Unknown;
        QualityInt = 0;
        InfectedInt = false;
        Name = L"";
        
        if (ClassName.find("Clay") != std::string::npos) {
            Name = L"Clay";
            TypeInt = TypeEnum::Clay;
            VariantInt = VariantEnum::Large;
        } else if (ClassName.find("Copper") != std::string::npos) {
            Name = L"Copper";
            TypeInt = TypeEnum::Copper;
        } else if (ClassName.find("Gold") != std::string::npos) {
            Name = L"Gold";
            TypeInt = TypeEnum::Gold;
        } else if (ClassName.find("Iron") != std::string::npos) {
            Name = L"Iron";
            TypeInt = TypeEnum::Iron;
        } else if (ClassName.find("Palium") != std::string::npos) {
            Name = L"Palium";
            TypeInt = TypeEnum::Palium;
        } else if (ClassName.find("Platinum") != std::string::npos) {
            Name = L"Platinum";
            TypeInt = TypeEnum::Platinum;
        } else if (ClassName.find("Silver") != std::string::npos) {
            Name = L"Silver";
            TypeInt = TypeEnum::Silver;
        } else if (ClassName.find("Stone") != std::string::npos) {
            if (ClassName.find("AZ2") != std::string::npos) {
                Name = L"Whitestone";
                TypeInt = TypeEnum::Whitestone;
            } else {
                Name = L"Stone";
                TypeInt = TypeEnum::Stone;
            }
        }

        if (ClassName.find("Small") != std::string::npos) {
            Name += L" S";
            VariantInt = VariantEnum::Small;
        } else if (ClassName.find("Medium") != std::string::npos) {
            Name += L" M";
            VariantInt = VariantEnum::Medium;
        } else if (ClassName.find("Large") != std::string::npos) {
            Name += L" L";
            VariantInt = VariantEnum::Large;
        }

        DisplayName = Name;
    }
    enum class TypeEnum : uint8_t {
        Unknown,
        Stone,
        Whitestone,
        Copper,
        Clay,
        Iron,
        Silver,
        Gold,
        Palium,
        Platinum,
        MAX
    };
    static inline std::vector<std::string> TypeString = {
        "Unknown",
        "Stone",
        "Whitestone",
        "Copper",
        "Clay",
        "Iron",
        "Silver",
        "Gold",
        "Palium",
        "Platinum",
    };

    enum class VariantEnum : uint8_t {
        Unknown,
        Small,
        Medium,
        Large,
        MAX
    };
    static inline std::vector<std::string> VariantString = {
        "Unknown",
        "Small",
        "Medium",
        "Large",
    };

private:
    TypeEnum TypeInt;
    VariantEnum VariantInt;
    uint8_t QualityInt;
    bool InfectedInt;
    std::wstring Name;

    static inline std::string Textures[static_cast<int>(TypeEnum::MAX)] = {
        "", // Unknown
        "/Game/UI/Icons/Icon_Stone.Icon_Stone", // Stone
        "/Game/UI/Icons/WT_Icon_WhiteStone.WT_Icon_WhiteStone", // Whitestone
        "/Game/UI/Icons/Icon_Ore_Copper.Icon_Ore_Copper", // Copper
        "/Game/UI/Icons/Icon_Ore_Clay.Icon_Ore_Clay", // Clay
        "/Game/UI/Icons/Icon_Ore_Iron.Icon_Ore_Iron", // Iron
        "/Game/UI/Icons/Icon_Ore_Silver.Icon_Ore_Silver", // Silver
        "/Game/UI/Icons/Icon_Ore_Gold.Icon_Ore_Gold", // Gold
        "/Game/UI/Icons/Icon_Ore_Palium.Icon_Ore_Palium", // Palium
        "/Game/UI/Icons/Icon_Ore_Platinum.Icon_Ore_Platinum", // Platinum
    };
public:
    EType ActorType() { return EType::Ore; }
    uint8_t Type() { 
        return static_cast<uint8_t>(TypeInt);
    }
    void setType(uint8_t x) {}
    uint8_t Quality() { return QualityInt; }
    void setQuality(uint8_t x) { QualityInt = x; }
    uint8_t Variant() { return static_cast<uint8_t>(VariantInt); }
    void setVariant(uint8_t x) {}
    std::string TexturePath() {
        return Textures[static_cast<int>(TypeInt)];
    }
    void setTexturePath(std::string x) {}
    bool Infected() {return InfectedInt; }
    void setInfected(bool isInfected) {InfectedInt = isInfected; }
};

class FEntryHunting : public FEntry {
public:
    FEntryHunting(SDK::AActor* A, std::string ClassName) : FEntry(A) {
        TypeInt = TypeEnum::Unknown;
        VariantInt = VariantEnum::Unknown;
        QualityInt = 0;
        InfectedInt = false;
        Name = L"";
        
        if (ClassName.find("BeachWalker") != std::string::npos) {
            Name = L"Ogopuu";
            TypeInt = TypeEnum::Ogopuu;
        } else if (ClassName.find("Cearnuk") != std::string::npos) {
            Name = L"Sernuk";
            TypeInt = TypeEnum::Cearnuk;
        } else if (ClassName.find("Chapaa") != std::string::npos) {
            Name = L"Chapaa";
            TypeInt = TypeEnum::Chapaa;
            if (ClassName.find("Chase") != std::string::npos) {
                TypeInt = TypeEnum::Chase;
                VariantInt = VariantEnum::Tier1;
            }
        } else if (ClassName.find("Fungopher") != std::string::npos) {
            Name = L"Shmole";
            TypeInt = TypeEnum::Shmole;
        } else if (ClassName.find("TreeClimber") != std::string::npos) {
            Name = L"Muujin";
            TypeInt = TypeEnum::TreeClimber;
        } else if (ClassName.find("Bubble") != std::string::npos) {
            Name = L"Chapaa Balloon";
            TypeInt = TypeEnum::Balloon;
        }

        if (ClassName.find("T1") != std::string::npos) {
            VariantInt = VariantEnum::Tier1;
        } else if (ClassName.find("T2") != std::string::npos) {
            Name = Prefix[static_cast<int>(TypeInt)][0] + Name;
            VariantInt = VariantEnum::Tier2;
        } else if (ClassName.find("T3") != std::string::npos) {
            Name = Prefix[static_cast<int>(TypeInt)][1] + Name;
            VariantInt = VariantEnum::Tier3;
        }

        DisplayName = Name;
    }

    enum class TypeEnum : uint8_t {
        Unknown,
        Chapaa,
        Cearnuk,
        TreeClimber,
        Ogopuu,
        Shmole,
        Balloon,
        Chase,
        MAX
    };
    static inline std::vector<std::string> TypeString = {
        "Unknown",
        "Chapaa",
        "Sernuk",
        "Muujin",
        "Ogopuu",
        "Shmole",
        "Balloon",
        "Chase",
    };

    enum class VariantEnum : uint8_t {
        Unknown,
        Tier1,
        Tier2,
        Tier3,
        MAX
    };
    static inline std::vector<std::string> VariantString = {
        "Unknown",
        "Tier1",
        "Tier2",
        "Tier3",
    };

private:
    TypeEnum TypeInt;
    VariantEnum VariantInt;
    uint8_t QualityInt;
    bool InfectedInt;
    std::wstring Name;

    static inline std::wstring Prefix[static_cast<int>(TypeEnum::MAX)][2] = {
        {}, // Unknown
        {   // Chapaa
            L"Striped ",
            L"Azure ",
        },
        {   // Cearnuk
            L"Elder ",
            L"Proudhorn ",
        },
        {   // TreeClimber
            L"Banded ",
            L"Bluebristle ",
        },
        {   // Ogupuu
            L"Emerald ",
            L"Waveback ",
        },
        {   // Shmole
            L"Elder ",
            L"Piksii ",
        },
        {   // Balloon
            L"Striped ",
            L"Azure ",
        },
        {}, // Chase
    };

    static inline std::string Textures[static_cast<int>(TypeEnum::MAX)][static_cast<int>(VariantEnum::MAX)] = {
    {}, // Unknown
    {   // Chapaa
        "", // Unknown
        "/Game/UI/Icons/Icon_Material_Chapaa_Tail_T1.Icon_Material_Chapaa_Tail_T1", // Tier1
        "/Game/UI/Icons/Icon_Material_Chapaa_Tail_T2.Icon_Material_Chapaa_Tail_T2", // Tier2
        "/Game/UI/Icons/Icon_Material_Chapaa_Tail_T3.Icon_Material_Chapaa_Tail_T3", // Tier3
    },
    {   // Cearnuk,
        "", // Unknown
        "/Game/UI/Icons/Icon_Material_Cearnuk_Antlers_T1.Icon_Material_Cearnuk_Antlers_T1", // Tier1
        "/Game/UI/Icons/Icon_Material_Cearnuk_Antlers_T2.Icon_Material_Cearnuk_Antlers_T2", // Tier2
        "/Game/UI/Icons/Icon_Material_Cearnuk_Antlers_T3.Icon_Material_Cearnuk_Antlers_T3", // Tier3
    },
    {   // TreeClimber,
        "", // Unknown
        "/Game/UI/Icons/WT_Icon_Material_Muujin_Fur_T1.WT_Icon_Material_Muujin_Fur_T1", // Tier1
        "/Game/UI/Icons/WT_Icon_Material_Muujin_Fur_T2.WT_Icon_Material_Muujin_Fur_T2", // Tier2
        "/Game/UI/Icons/WT_Icon_Material_Muujin_Fur_T3.WT_Icon_Material_Muujin_Fur_T3", // Tier3
    },
    {   // Beachwalker,
        "", // Unknown
        "/Game/UI/Icons/WT_Icon_Material_Beachwalker_Scale_T1.WT_Icon_Material_Beachwalker_Scale_T1", // Tier1
        "/Game/UI/Icons/WT_Icon_Material_Beachwalker_Scale_T2.WT_Icon_Material_Beachwalker_Scale_T2", // Tier2
        "/Game/UI/Icons/WT_Icon_Material_Beachwalker_Scale_T3.WT_Icon_Material_Beachwalker_Scale_T3", // Tier3
    },
    {   // Fungopher,
        "", // Unknown
        "/Game/UI/Icons/WT_Icon_Material_Spore_T1.WT_Icon_Material_Spore_T1", // Tier1
        "/Game/UI/Icons/WT_Icon_Material_Spore_T2.WT_Icon_Material_Spore_T2", // Tier2
        "/Game/UI/Icons/WT_Icon_Material_Spore_T3.WT_Icon_Material_Spore_T3", // Tier3
    },
    {   // Balloon
        "", // Unknown
        "/Game/UI/Icons/WT_Icon_Decor_MajiMarket_67_Deco_Balloon_Simple.WT_Icon_Decor_MajiMarket_67_Deco_Balloon_Simple", // Tier 1
        "/Game/UI/Icons/WT_Icon_Decor_MajiMarket_68_Deco_Balloon_ChapaaHead.WT_Icon_Decor_MajiMarket_68_Deco_Balloon_ChapaaHead", // Tier 2
        "/Game/UI/Icons/WT_Icon_Decor_MajiMarket_69_Deco_Balloon_ChapaaHat.WT_Icon_Decor_MajiMarket_69_Deco_Balloon_ChapaaHat", // Tier 3
    }
    };
public:
    EType ActorType() {
        if (TypeInt == TypeEnum::Balloon) { return EType::Bubble; }
        return EType::Animal;
    }
    uint8_t Type() { 
        return static_cast<uint8_t>(TypeInt);
    }
    void setType(uint8_t x) {}
    uint8_t Quality() { return QualityInt; }
    void setQuality(uint8_t x) { QualityInt = x; }
    uint8_t Variant() { return static_cast<uint8_t>(VariantInt); }
    void setVariant(uint8_t x) {}
    std::string TexturePath() {
        return Textures[static_cast<int>(TypeInt)][static_cast<int>(VariantInt)];
    }
    void setTexturePath(std::string x) {}
    bool Infected() {return InfectedInt; }
    void setInfected(bool isInfected) {InfectedInt = isInfected; }
};

class FEntryGatherable : public FEntry {
public:
    FEntryGatherable(SDK::AActor* A, std::string ClassName) : FEntry(A) {
        TypeInt = TypeEnum::Unknown;
        VariantInt = 0;
        QualityInt = 0;
        InfectedInt = false;
        Name = L"";
        
        if (ClassName.find("Oyster") != std::string::npos) {
            Name = L"Unopened Oyster";
            TypeInt = TypeEnum::Oyster;
        } else if (ClassName.find("Coral") != std::string::npos) {
            Name = L"Coral";
            TypeInt = TypeEnum::Coral;
        } else if (ClassName.find("MushroomBlue") != std::string::npos) {
            Name = L"Brightshroom";
            TypeInt = TypeEnum::MushroomBlue;
        } else if (ClassName.find("MushroomR") != std::string::npos) {
            Name = L"Mountain Morel";
            TypeInt = TypeEnum::MushroomRed;
        } else if (ClassName.find("HeartdropLilly") != std::string::npos) {
            Name = L"Heartdrop Lilly";
            TypeInt = TypeEnum::Heartdrop;
        } else if (ClassName.find("DragonsBeard") != std::string::npos) {
            Name = L"Dragon's Beard Peat";
            TypeInt = TypeEnum::DragonsBeard;
        } else if (ClassName.find("EmeraldCarpet") != std::string::npos) {
            Name = L"Emerald Carpet Moss";
            TypeInt = TypeEnum::EmeraldCarpet;
        } else if (ClassName.find("PoisonFlower") != std::string::npos) {
            Name = L"Briar Daisy";
            TypeInt = TypeEnum::PoisonFlower;
        } else if (ClassName.find("Seashell") != std::string::npos) {
            Name = L"Shell";
            TypeInt = TypeEnum::Shell;
        } else if (ClassName.find("DariCloves") != std::string::npos) {
            Name = L"Dari Cloves";
            TypeInt = TypeEnum::DariCloves;
        } else if (ClassName.find("HeatRoot") != std::string::npos) {
            Name = L"Heat Root";
            TypeInt = TypeEnum::HeatRoot;
        } else if (ClassName.find("Spiced_Sprouts") != std::string::npos) {
            Name = L"Spice Sprouts";
            TypeInt = TypeEnum::SpicedSprouts;
        } else if (ClassName.find("SundropLillies") != std::string::npos) {
            Name = L"Sundrop Lily";
            TypeInt = TypeEnum::Sundrop;
        } else if (ClassName.find("SweetLeaves") != std::string::npos) {
            Name = L"Sweet Leaf";
            TypeInt = TypeEnum::SweetLeaves;
        } else if (ClassName.find("WaterFlower") != std::string::npos) {
            Name = L"Crystal Lake Lotus";
            TypeInt = TypeEnum::WaterFlower;
        } else if (ClassName.find("WildGarlic") != std::string::npos) {
            Name = L"Wild Garlic";
            TypeInt = TypeEnum::Garlic;
        } else if (ClassName.find("Ginger") != std::string::npos) {
            Name = L"Wild Ginger";
            TypeInt = TypeEnum::Ginger;
        } else if (ClassName.find("GreenOnion") != std::string::npos) {
            Name = L"Wild Green Onion";
            TypeInt = TypeEnum::GreenOnion;
        } else if (ClassName.find("StaircaseMushroom") != std::string::npos) {
            Name = L"Staircase Mushroom";
            TypeInt = TypeEnum::StaircaseMushroom;
        } else if (ClassName.find("FloatfishMushroom") != std::string::npos) {
            Name = L"Floatfish Mushroom";
            TypeInt = TypeEnum::FloatfishMushroom;
        } else if (ClassName.find("ElderwoodOrchid") != std::string::npos) {
            Name = L"Elderwood Orchid";
            TypeInt = TypeEnum::ElderwoodOrchid;
        } else if (ClassName.find("ElderwoodLotus") != std::string::npos) {
            Name = L"Elderwood Lotus";
            TypeInt = TypeEnum::ElderwoodLotus;
        } else if (ClassName.find("PiksiiBerries") != std::string::npos) {
            Name = L"Piksii Berries";
            TypeInt = TypeEnum::PiksiiBerries;
        } else if (ClassName.find("KopaaNut") != std::string::npos) {
            Name = L"Kopaa Nut";
            TypeInt = TypeEnum::KopaaNut;
        } else if (ClassName.find("ElderClamMushroom") != std::string::npos) {
            Name = L"Elder Clam Mushroom";
            TypeInt = TypeEnum::ElderClamMushroom;
        } else if (ClassName.find("BatterflyBeans") != std::string::npos) {
            Name = L"Batterfly Beans";
            TypeInt = TypeEnum::BatterflyBeans;
        } else if (ClassName.find("Flowtato") != std::string::npos) {
            Name = L"Flowtato";
            TypeInt = TypeEnum::FlowTato;
        } else if (ClassName.find("Elderflower") != std::string::npos) {
            Name = L"Elderflower";
            TypeInt = TypeEnum::Elderflower;
        } else if (ClassName.find("EchoEssence") != std::string::npos) {
            Name = L"Infected Essence";
            TypeInt = TypeEnum::EchoEssence;
        } else if (ClassName.find("Honey") != std::string::npos) {
            Name = L"Honey";
            TypeInt = TypeEnum::Honey;
        }

        DisplayName = Name;
        if (TypeInt == TypeEnum::Unknown) {
            std::cout << "\nUnknown Gatherable Actor: " << ClassName << "\n";
        }
    }

    enum class TypeEnum : uint8_t {
        Unknown,
        Oyster,
        Coral,
        MushroomBlue,
        MushroomRed,
        Heartdrop,
        DragonsBeard,
        EmeraldCarpet,
        PoisonFlower,
        Shell,
        DariCloves,
        HeatRoot,
        SpicedSprouts,
        Sundrop,
        SweetLeaves,
        WaterFlower,
        Garlic,
        Ginger,
        GreenOnion,
        StaircaseMushroom,
        FloatfishMushroom,
        ElderwoodOrchid,
        ElderwoodLotus,
        PiksiiBerries,
        KopaaNut,
        ElderClamMushroom,
        BatterflyBeans,
        FlowTato,
        Elderflower,
        EchoEssence,
        Honey,
        MAX
    };
    static inline std::vector<std::string> TypeString = {
        "Unknown",
        "Oyster",
        "Coral",
        "Mushroom Blue",
        "Mushroom Red",
        "Heartdrop",
        "Dragons Beard",
        "Emerald Carpet",
        "Poison Flower",
        "Shell",
        "Dari Cloves",
        "Heat Root",
        "Spiced Sprouts",
        "Sundrop",
        "Sweet Leaves",
        "Water Flower",
        "Garlic",
        "Ginger",
        "Green Onion",
        "Staircase Mushroom",
        "Floatfish Mushroom",
        "Elderwood Orchid",
        "Elderwood Lotus",
        "Piksii Berries",
        "Kopaa Nut",
        "Elder Clam Mushroom",
        "Batterfly Beans",
        "Flowtato",
        "Elderflower",
        "EchoEssence",
        "Honey"
    };

private:
    TypeEnum TypeInt;
    uint8_t VariantInt;
    uint8_t QualityInt;
    bool InfectedInt;
    std::wstring Name;

    static inline std::string Textures[static_cast<int>(TypeEnum::MAX)] = {
        "", //Unknown
        "/Game/UI/Icons/Icon_Oyster.Icon_Oyster", //Oyster
        "/Game/UI/Icons/Icon_Coral.Icon_Coral", //Coral
        "/Game/UI/Icons/Icon_Crop_MushroomBlue.Icon_Crop_MushroomBlue", //MushroomBlue
        "/Game/UI/Icons/Icon_Crop_MushroomRed.Icon_Crop_MushroomRed", //MushroomRed
        "/Game/UI/Icons/Icon_Flower_Heartdrop.Icon_Flower_Heartdrop", //Heartdrop
        "/Game/UI/Icons/Icon_Moss_Rare.Icon_Moss_Rare", //DragonsBeard
        "/Game/UI/Icons/Icon_Moss_Common.Icon_Moss_Common", //EmeraldCarpet
        "/Game/UI/Icons/Icon_Flower_Daisy_Briar.Icon_Flower_Daisy_Briar", //PoisonFlower
        "/Game/UI/Icons/Icon_Shell.Icon_Shell", //Shell
        "/Game/UI/Icons/Icon_Flower_DariClove.Icon_Flower_DariClove", //DariCloves
        "/Game/UI/Icons/Icon_Spice_Heatroot.Icon_Spice_Heatroot", //HeatRoot
        "/Game/UI/Icons/Icon_Forage_SpiceSprouts.Icon_Forage_SpiceSprouts", //SpicedSprouts
        "/Game/UI/Icons/Icon_Flower_SundropLily.Icon_Flower_SundropLily", //Sundrop
        "/Game/UI/Icons/Icon_Spice_SweetLeaves.Icon_Spice_SweetLeaves", //SweetLeaves
        "/Game/UI/Icons/Icon_Flower_Lotus.Icon_Flower_Lotus", //WaterFlower
        "/Game/UI/Icons/Icon_Forage_WildGarlic.Icon_Forage_WildGarlic", //Garlic
        "/Game/UI/Icons/Icon_Foragable_Spice_Ginger.Icon_Foragable_Spice_Ginger", //Ginger
        "/Game/UI/Icons/Icon_Foragable_Spice_GreenOnion.Icon_Foragable_Spice_GreenOnion", //GreenOnion
        "/Game/UI/Icons/WT_Icon_Mushroom_Staircase.WT_Icon_Mushroom_Staircase", //StaircaseMushroom
        "/Game/UI/Icons/WT_Icon_Mushroom_Floatfish.WT_Icon_Mushroom_Floatfish", //FloatfishMushroom
        "/Game/UI/Icons/WT_Icon_Elderwood_Orchid.WT_Icon_Elderwood_Orchid", //ElderwoodOrchid
        "/Game/UI/Icons/WT_Icon_Elderwood_Lotus.WT_Icon_Elderwood_Lotus", //ElderwoodLotus
        "/Game/UI/Icons/WT_Icon_Berry_Piksii.WT_Icon_Berry_Piksii", //PiksiiBerries
        "/Game/UI/Icons/WT_Icon_Nut_Kopaa.WT_Icon_Nut_Kopaa", //KopaaNut
        "/Game/UI/Icons/WT_Icon_Mushroom_Elder_Clam.WT_Icon_Mushroom_Elder_Clam", //ElderClamMushroom
        "/Game/UI/Icons/WT_Icon_BatterflyBeans.WT_Icon_BatterflyBeans", //BatterflyBeans
        "/Game/UI/Icons/WT_Icon_Flotato.WT_Icon_Flotato", //FlowTato
        "/Game/UI/Icons/WT_Icon_Elderflower.WT_Icon_Elderflower", //Elderflower
        "/Game/UI/Icons/Icon_Echo_Essence.Icon_Echo_Essence", //EchoEssence
        "/Game/UI/Icons/Icon_Crop_Honey.Icon_Crop_Honey", //Honey
    };
public:
    EType ActorType() { return EType::Forage; }
    uint8_t Type() { 
        return static_cast<uint8_t>(TypeInt);
    }
    void setType(uint8_t x) {}
    uint8_t Quality() { return QualityInt; }
    void setQuality(uint8_t x) { QualityInt = x; }
    uint8_t Variant() { return VariantInt; }
    void setVariant(uint8_t x) { VariantInt = x; }
    std::string TexturePath() {
        return Textures[static_cast<int>(TypeInt)];
    }
    void setTexturePath(std::string x) {}
    bool Infected() {return InfectedInt; }
    void setInfected(bool isInfected) {InfectedInt = isInfected; }
};

class FEntryBug : public FEntry {
public:
    FEntryBug(SDK::AActor* A, std::string ClassName) : FEntry(A) {
        TypeInt = TypeEnum::Unknown;
        VariantInt = VariantEnum::Unknown;
        QualityInt = 0;
        InfectedInt = false;
        Name = L"";

        if (ClassName.find("Batterfly") != std::string::npos) {
            TypeInt = TypeEnum::Batterfly;
            // is a consistent naming scheme too much to ask for?
            if (ClassName.find("Cotton") != std::string::npos) {
                VariantInt = VariantEnum::Common;
            } else if (ClassName.find("Day") != std::string::npos) {
                VariantInt = VariantEnum::Uncommon;
            } else if (ClassName.find("Night") != std::string::npos) {
                VariantInt = VariantEnum::Uncommon2;
            } else if (ClassName.find("Vamp") != std::string::npos) {
                VariantInt = VariantEnum::Epic;
            }
        } else if (ClassName.find("AZ2_Beetle") != std::string::npos) {
            TypeInt = TypeEnum::BeetleAZ2;
            if (ClassName.find("Blood") != std::string::npos) {
                VariantInt = VariantEnum::Rare;
            } else if (ClassName.find("Draugr") != std::string::npos) {
                VariantInt = VariantEnum::Uncommon;
            }
        } else if (ClassName.find("Beetle") != std::string::npos) {
            TypeInt = TypeEnum::Beetle;
        } else if (ClassName.find("Bee") != std::string::npos) {
            TypeInt = TypeEnum::Bee;
        } else if (ClassName.find("Butterfly") != std::string::npos) {
            TypeInt = TypeEnum::Butterfly;
        } else if (ClassName.find("Butterfly") != std::string::npos) {
            TypeInt = TypeEnum::Butterfly;
        } else if (ClassName.find("Cicada") != std::string::npos) {
            TypeInt = TypeEnum::Cicada;
        } else if (ClassName.find("Crab") != std::string::npos) {
            TypeInt = TypeEnum::Crab;
        } else if (ClassName.find("Cricket") != std::string::npos) {
            TypeInt = TypeEnum::Cricket;
        } else if (ClassName.find("Dragonfly") != std::string::npos) {
            TypeInt = TypeEnum::Dragonfly;
        } else if (ClassName.find("Glowbug") != std::string::npos) {
            TypeInt = TypeEnum::Glowbug;
        } else if (ClassName.find("Ladybug") != std::string::npos) {
            TypeInt = TypeEnum::Ladybug;
        } else if (ClassName.find("Mantis") != std::string::npos) {
            TypeInt = TypeEnum::Mantis;
        } else if (ClassName.find("AZ2_Moth") != std::string::npos) {
            TypeInt = TypeEnum::MothAZ2;
        } else if (ClassName.find("Moth") != std::string::npos) {
            TypeInt = TypeEnum::Moth;
        } else if (ClassName.find("Pede") != std::string::npos) {
            TypeInt = TypeEnum::Pede;
        } else if (ClassName.find("Piksii") != std::string::npos) {
            TypeInt = TypeEnum::Piksii;
            if (ClassName.find("Forest") != std::string::npos) {
                VariantInt = VariantEnum::Common;
            } else if (ClassName.find("Stair") != std::string::npos) {
                VariantInt = VariantEnum::Uncommon;
            }
        } else if ((ClassName.find("RockHopper") != std::string::npos) || (ClassName.find("Rockhopper") != std::string::npos)) {
            // classic S6, can't even keep case the same
            TypeInt = TypeEnum::RockHopper;
            if (ClassName.find("Flame") != std::string::npos) {
                VariantInt = VariantEnum::Rare;
            } else if (ClassName.find("Granite") != std::string::npos) {
                VariantInt = VariantEnum::Common;
            } else if (ClassName.find("Lantern") != std::string::npos) {
                VariantInt = VariantEnum::Epic;
            }
        } else if (ClassName.find("Snail") != std::string::npos) {
            TypeInt = TypeEnum::Snail;
        }

        if (ClassName.ends_with("C_C")) {
            VariantInt = VariantEnum::Common;
        } else if (ClassName.ends_with("U2_C")) {
            VariantInt = VariantEnum::Uncommon2;
        } else if (ClassName.ends_with("U_C") || ClassName.ends_with("U1_C")) {
            VariantInt = VariantEnum::Uncommon;
        } else if (ClassName.ends_with("R2_C")) {
            VariantInt = VariantEnum::Rare2;
        } else if (ClassName.ends_with("R_C") || ClassName.ends_with("R1_C")) {
            VariantInt = VariantEnum::Rare;
        } else if (ClassName.ends_with("E_C")) {
            VariantInt = VariantEnum::Epic;
        }

        if (TypeInt != TypeEnum::Unknown || VariantInt != VariantEnum::Unknown) {
            Name = NameMap[static_cast<int>(TypeInt)][static_cast<int>(VariantInt)];
        }

        DisplayName = Name;
        if (TypeInt == TypeEnum::Unknown || VariantInt == VariantEnum::Unknown) {
            std::cout << "\nUnknown Bug Actor: " << ClassName << "\n\n";
        }
    }

    enum class TypeEnum : uint8_t {
        Unknown,
        Batterfly,
        Bee,
        Beetle,
        BeetleAZ2,
        Butterfly,
        Cicada,
        Crab,
        Cricket,
        Dragonfly,
        Glowbug,
        Ladybug,
        Mantis,
        Moth,
        MothAZ2,
        Pede,
        Piksii,
        RockHopper,
        Snail,
        MAX
    };
    static inline std::vector<std::string> TypeString = {
        "Unknown",
        "Batterfly",
        "Bee",
        "Beetle",
        "BeetleAZ2",
        "Butterfly",
        "Cicada",
        "Crab",
        "Cricket",
        "Dragonfly",
        "Glowbug",
        "Ladybug",
        "Mantis",
        "Moth",
        "MothAZ2",
        "Pede",
        "Piksii",
        "RockHopper",
        "Snail",
    };

    enum class VariantEnum : uint8_t {
        Unknown,
        Common,
        Uncommon,
        Uncommon2,
        Rare,
        Rare2,
        Epic,
        MAX
    };
    static inline std::vector<std::string> VariantString = {
        "Unknown",
        "Common",
        "Uncommon",
        "Uncommon2",
        "Rare",
        "Rare2",
        "Epic",
    };

private:
    TypeEnum TypeInt;
    VariantEnum VariantInt;
    uint8_t QualityInt;
    bool InfectedInt;
    std::wstring Name;

    static inline std::string Textures[static_cast<int>(TypeEnum::MAX)][static_cast<int>(VariantEnum::MAX)] = {
        {}, // Unknown
        {   // Batterfly
            "", // Unknown
            "/Game/UI/Icons/WT_Icon_Bug_Batterfly_Cottonhop.WT_Icon_Bug_Batterfly_Cottonhop", // Common
            "/Game/UI/Icons/WT_Icon_Bug_Batterfly_Dayshadow.WT_Icon_Bug_Batterfly_Dayshadow", // Uncommon
            "/Game/UI/Icons/WT_Icon_Bug_Batterfly_Nightshadow.WT_Icon_Bug_Batterfly_Nightshadow", // Uncommon2
            "", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Bee
            "", // Unknown
            "", // Common
            "/Game/UI/Icons/Icon_Bug_Bee_Bahari.Icon_Bug_Bee_Bahari", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Bee_GoldenGlory.Icon_Bug_Bee_GoldenGlory", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Beetle
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Beetle_SpottedStinkbug.Icon_Bug_Beetle_SpottedStinkbug", // Common
            "/Game/UI/Icons/Icon_Bug_Beetle_ProudhornedStag.Icon_Bug_Beetle_ProudhornedStag", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Beetle_Raspberry.Icon_Bug_Beetle_Raspberry", // Rare
            "", // Rare2
            "/Game/UI/Icons/Icon_Bug_Beetle_AncientAmber.Icon_Bug_Beetle_AncientAmber", // Epic
        },
        {   // BeetleAZ2
            "", // Unknown
            "", // Common
            "/Game/UI/Icons/WT_Icon_Bug_Beetle_Draugr.WT_Icon_Bug_Beetle_Draugr", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/WT_Icon_Bug_Beetle_Blood.WT_Icon_Bug_Beetle_Blood", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Butterfly
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Butterfly_CommonBlue.Icon_Bug_Butterfly_CommonBlue", // Common
            "/Game/UI/Icons/Icon_Bug_Butterfly_Duskwing.Icon_Bug_Butterfly_Duskwing", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Butterfly_Brighteye.Icon_Bug_Butterfly_Brighteye", // Rare
            "", // Rare2
            "/Game/UI/Icons/Icon_Bug_Butterfly_RainbowTipped.Icon_Bug_Butterfly_RainbowTipped", // Epic
        },
        {   // Cicada
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Cicada_CommonBark.Icon_Bug_Cicada_CommonBark", // Common
            "/Game/UI/Icons/Icon_Bug_Cicada_Cerulean.Icon_Bug_Cicada_Cerulean", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Cicada_Spitfire.Icon_Bug_Cicada_Spitfire", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Crab
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Crab_Bahari.Icon_Bug_Crab_Bahari", // Common
            "/Game/UI/Icons/Icon_Bug_Crab_Spineshell.Icon_Bug_Crab_Spineshell", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Crab_Vampire.Icon_Bug_Crab_Vampire", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Cricket
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Cricket_CommonField.Icon_Bug_Cricket_CommonField", // Common
            "/Game/UI/Icons/Icon_Bug_Cricket_GardenLeafhopper.Icon_Bug_Cricket_GardenLeafhopper", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Cricket_AzureStonehopper.Icon_Bug_Cricket_AzureStonehopper", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Dragonfly
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Dragonfly_Brushtail.Icon_Bug_Dragonfly_Brushtail", // Common
            "/Game/UI/Icons/Icon_Bug_Dragonfly_Inky.Icon_Bug_Dragonfly_Inky", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Dragonfly_Firebreathing.Icon_Bug_Dragonfly_Firebreathing", // Rare
            "", // Rare2
            "/Game/UI/Icons/Icon_Bug_Dragonfly_Jewelwing.Icon_Bug_Dragonfly_Jewelwing", // Epic
        },
        {   // Glowbug
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Glowbug_PaperLantern.Icon_Bug_Glowbug_PaperLantern", // Common
            "", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Glowbug_Bahari.Icon_Bug_Glowbug_Bahari", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Ladybug
            "", // Unknown
            "", // Common
            "/Game/UI/Icons/Icon_Bug_Ladybug_Garden.Icon_Bug_Ladybug_Garden", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Ladybug_Princess.Icon_Bug_Ladybug_Princess", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Mantis
            "", // Unknown
            "", // Common
            "/Game/UI/Icons/Icon_Bug_Mantis_Garden.Icon_Bug_Mantis_Garden", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Mantis_Spotted.Icon_Bug_Mantis_Spotted", // Rare
            "/Game/UI/Icons/Icon_Bug_Mantis_Leafstalker.Icon_Bug_Mantis_Leafstalker", // Rare2
            "/Game/UI/Icons/Icon_Bug_Mantis_Fairy.Icon_Bug_Mantis_Fairy", // Epic
        },
        {   // Moth
            "", // Unknown
            "/Game/UI/Icons/Icon_Bug_Moth_KilimaNight.Icon_Bug_Moth_KilimaNight", // Common
            "/Game/UI/Icons/Icon_Bug_Moth_LunarFairy.Icon_Bug_Moth_LunarFairy", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Moth_GossamerVeil.Icon_Bug_Moth_GossamerVeil", // Rare
            "", // Rare2
            "", // Epic
        },
        {}, // MothAZ2
        {   // Pede
            "", // Unknown
            "", // Common
            "/Game/UI/Icons/Icon_Bug_Millipede_Garden.Icon_Bug_Millipede_Garden", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Millipede_Hairy.Icon_Bug_Millipede_Hairy", // Rare
            "/Game/UI/Icons/Icon_Bug_Millipede_Scintillating.Icon_Bug_Millipede_Scintillating", // Rare2
            "", // Epic
        },
        {   // Piksii
            "", // Unknown
            "/Game/UI/Icons/WT_Icon_Bug_Piksii_Forest.WT_Icon_Bug_Piksii_Forest", // Common
            "/Game/UI/Icons/WT_Icon_Bug_Piksii_Brightshroom.WT_Icon_Bug_Piksii_Brightshroom", // Uncommon
            "", // Uncommon2
            "", // Rare
            "", // Rare2
            "", // Epic
        },
        {   // Rockhopper
            "", // Unknown
            "/Game/UI/Icons/WT_Icon_Bug_Rockhopper_Grumpy_Granite.WT_Icon_Bug_Rockhopper_Grumpy_Granite", // Common
            "", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/WT_Icon_Bug_Rockhopper_Flamehorned.WT_Icon_Bug_Rockhopper_Flamehorned", // Rare
            "", // Rare2
            "/Game/UI/Icons/WT_Icon_Bug_Rockhopper_Floating_Lantern.WT_Icon_Bug_Rockhopper_Floating_Lantern", // Epic
        },
        {   // Snail
            "", // Unknown
            "", // Common
            "/Game/UI/Icons/Icon_Bug_Snail_Garden.Icon_Bug_Snail_Garden", // Uncommon
            "", // Uncommon2
            "/Game/UI/Icons/Icon_Bug_Snail_Stripeshell.Icon_Bug_Snail_Stripeshell", // Rare
            "", // Rare2
            "", // Epic
        },
    };

    static inline std::wstring NameMap[static_cast<int>(TypeEnum::MAX)][static_cast<int>(VariantEnum::MAX)] = {
        {}, // Unknown
        {   // Batterfly
            L"",L"Blushing Batterfly",L"Sunburst Batterfly",L"Nightshadow Batterfly",L"",L"",L"Vampire Batterfly"
        },
        {   // Bee
            L"",L"",L"Bahari Bee",L"",L"Golden Glory Bee",L"",L""
        },
        {   // Beetle
            L"",L"Spotted Stinkbug",L"Proudhorned Stag Beetle",L"",L"Raspberry Beetle",L"",L"Ancient Amber Beetle"
        },
        {   // BeetleAZ2
            L"",L"",L"Draugr Beetle",L"",L"Blood Beetle",L"",L""
        },
        {   // Butterfly
            L"",L"Common Blue Butterfly",L"Duskwing Butterfly",L"",L"Brighteye Butterfly",L"",L"Rainbow-tipped Butterfly"
        },
        {   // Cicada
            L"",L"Common Bark Cicada",L"Cerulean Cicada",L"",L"Spitfire Cicada",L"",L""
        },
        {   // Crab
            L"",L"Bahari Crab",L"Spineshell Crab",L"",L"Vampire Crab",L"",L""
        },
        {   // Cricket
            L"",L"Common Field Cricket",L"Garden Leafhopper",L"",L"",L"",L""
        },
        {   // Dragonfly
            L"",L"Brushtail Dragonfly",L"Inky Dragonfly",L"",L"Firebreathing Dragonfly",L"",L"Jewelwing Dragonfly"
        },
        {   // Glowbug
            L"",L"Paper Lantern Bug",L"",L"",L"Bahari Glowbug",L"",L""
        },
        {   // Ladybug
            L"",L"",L"Garden Ladybug",L"",L"Princess Ladybug",L"",L""
        },
        {   // Mantis
            L"",L"",L"Garden Mantis",L"",L"Spotted Mantis",L"Leafstalker Mantis",L"Fairy Mantis"
        },
        {   // Moth
            L"",L"Kilima Night Moth",L"Lunar Fairy Moth",L"",L"Gossamer Veil Moth",L"",L""
        },
        {   // MothAZ2 (Are these even in the game yet?)
            L"",L"Hummingbird Moth",L"Whispering Widow Moth",L"",L"Kitsuu Moth",L"",L"Witch's Eye Moth"
        },
        {   // Pede
            L"",L"",L"Garden Millipede",L"",L"Hairy Millipede",L"Scintillating Centipede",L""
        },
        {   // Piksii
            L"",L"Veil Piksii",L"Cave Piksii",L"",L"",L"",L""
        },
        {   // RockHopper
            L"",L"Grumpy Granite Rockhopper",L"",L"",L"Flame-Horned Rockhopper",L"",L"Floating Lantern Rockhopper"
        },
        {   // Snail
            L"",L"",L"Garden Snail",L"",L"Stripeshell Snail",L"",L""
        },
    };


public:
    EType ActorType() { return EType::Bug; }
    uint8_t Type() { return static_cast<uint8_t>(TypeInt); }
    void setType(uint8_t x) {}
    uint8_t Quality() { return QualityInt; }
    void setQuality(uint8_t x) { QualityInt = x; }
    uint8_t Variant() { return static_cast<uint8_t>(VariantInt); }
    void setVariant(uint8_t x) { VariantInt = static_cast<VariantEnum>(x); }
    std::string TexturePath() {
        return Textures[static_cast<int>(TypeInt)][static_cast<int>(VariantInt)];
    }
    void setTexturePath(std::string x) {}
    bool Infected() {return InfectedInt; }
    void setInfected(bool isInfected) {InfectedInt = isInfected; }
};

enum class ELootBagType : uint8_t {
    Unknown,
    Hunting,
    Bug,
    Mining,
    Chopping,
    MAX,
};

enum class EOneOffs : uint8_t {
    Player,
    NPC,
    FishHook,
    FishPool,
    Loot,
    Quest,
    RummagePiles,
    Stables,
    Others,
    Treasure,
    TimedDrop,
    Relic,
    Decor,
    MAX
};
static inline std::vector<std::string> EOneOffsString = {
    "Player",
    "NPC",
    "FishHook",
    "FishPool",
    "Loot",
    "Quest",
    "RummagePiles",
    "Stables",
    "Others",
    "Treasure",
    "TimedDrop",
    "Relic",
    "Decor",
};

inline std::map<std::string, std::string> CLASS_NAME_ALIAS = {

    // Fishing Nodes
    {"BP_WaterPlane_Fishing_OceanAZ1_SQ_C", "Coast"},
    {"BP_WaterPlane_Fishing_PondVillage_SQ_C", "Pond"},
    {"BP_WaterPlane_Fishing_LakeVillage_SQ_C", "Lake"},
    {"BP_WaterPlane_Fishing_RiverVillage_SQ_C", "Kilima River"},
    {"BP_WaterPlane_Fishing_RiverAZ1_SQ_C", "Bahari River"},
    {"BP_WaterPlane_Fishing_AZ1_Cave_SQ_C", "Cave"},

    // Fish
    {"BP_FishingJackpot_C", "Waterlogged Chest"},
    {"BP_FishingRecipeBook_C", "Recipe Book"},
    {"BP_Fish_AlbinoEeel_C", "Albino Eeel"},
    {"BP_Fish_Alligator_Gar_C", "Alligator Gar"},
    {"BP_Fish_AncientFish_C", "Ancient Fish"},
    {"BP_Fish_BahariBream_C", "Bahari Bream"},
    {"BP_Fish_Bahari_Pike_C", "Bahari Pike"},
    {"BP_Fish_Barracuda_C", "Barracuda"},
    {"BP_Fish_BatRay_C", "Bat Ray"},
    {"BP_Fish_Beluga_Sturgeon_C", "Beluga Sturgeon"},
    {"BP_Fish_Bigeye_Tuna_C", "Bigeye_Tuna"},
    {"BP_Fish_Black_Sea_Bass_C", "Black Sea Bass"},
    {"BP_Fish_Blobfish_C", "Blobfish"},
    {"BP_Fish_BlueMarlin_C", "Blue Marlin"},
    {"BP_Fish_Blue_Spotted_Ray_C", "Blue Spotted Ray"},
    {"BP_Fish_Cactus_Moray_C", "Cactus Moray"},
    {"BP_Fish_CalicoKoi_C", "Calico Koi"},
    {"BP_Fish_CantankerousKoi_C", "CantankerousKoi"},
    {"BP_Fish_Channel_Catfish_C", "Channel Catfish"},
    {"BP_Fish_Chub_C", "Chub"},
    {"BP_Fish_Cloudfish_C", "Cloudfish"},
    {"BP_Fish_Codfish_C", "Codfish"},
    {"BP_Fish_Crimson_Fangtooth_C", "Crimson Fangtooth"},
    {"BP_Fish_Crucian_Carp_C", "Crucian Carp"},
    {"BP_Fish_Cutthroat_Trout_C", "Cutthroat Trout"},
    {"BP_Fish_Dawnray_C", "Dawnray"},
    {"BP_Fish_Duskray_C", "Duskray"},
    {"BP_Fish_Enchanted_Pupfish_C", "Enchanted Pupfish"},
    {"BP_Fish_Energized_Piranha_C", "Energized Piranha"},
    {"BP_Fish_EyelessMinnow_C", "Eyeless Minnow"},
    {"BP_Fish_FairyCarp_C", "Fairy Carp"},
    {"BP_Fish_Fathead_Minnow_C", "Fathead Minnow"},
    {"BP_Fish_Flametongue_Ray_C", "Flametongue Ray"},
    {"BP_Fish_FreshwaterEel_C", "Freshwater Eel"},
    {"BP_Fish_Giant_Goldfish_C", "Giant Goldfish"},
    {"BP_Fish_Giant_Kilima_Stingray_C", "Giant Kilima Stingray"},
    {"BP_Fish_Gillyfin_C", "Gillyfin"},
    {"BP_Fish_GoldenSalmon_C", "Golden Salmon"},
    {"BP_Fish_Honey_Loach_C", "Honey Loach"},
    {"BP_Fish_Hypnotic_Moray_C", "Hypnotic Moray"},
    {"BP_Fish_Indigo_Lamprey_C", "Indigo Lamprey"},
    {"BP_Fish_Kenjis_Carp_C", "Kenli's Carp"},
    {"BP_Fish_KilimaCatFish_C", "Kilima Catfish"},
    {"BP_Fish_Kilima_Grayling_C", "Kilima Grayling"},
    {"BP_Fish_Kilima_Redfin_C", "Kilima Redfin"},
    {"BP_Fish_LargemouthBass_C", "Largemouth Bass"},
    {"BP_Fish_Midnight_Paddlefish_C", "Midnight Paddlefish"},
    {"BP_Fish_Mirror_Carp_C", "Mirror Carp"},
    {"BP_Fish_Mottled_Gobi_C", "Mottled Gobi"},
    {"BP_Fish_Mudminnow_C", "Mudminnow"},
    {"BP_Fish_MutatedAngler_C", "Mutated Angler"},
    {"BP_Fish_Oily_Anchovy_C", "Oily Anchovy"},
    {"BP_Fish_Orange_Bluegill_C", "Orange Bluegill"},
    {"BP_Fish_Paddlefish_C", "Paddlefish"},
    {"BP_Fish_PaintedPerch_C", "Painted Perch"},
    {"BP_Fish_Platinum_Chad_C", "Platinum Chad"},
    {"BP_Fish_PrismTrout_C", "Prism Trout"},
    {"BP_Fish_RadiantSunfish_C", "Radiant Sunfish"},
    {"BP_Fish_Rainbow_Trout_C", "Rainbow Trout"},
    {"BP_Fish_Red-bellied_piranha_C", "Red-bellied Piranha"},
    {"BP_Fish_RibbontailRay_C", "Ribbontail Ray"},
    {"BP_Fish_Rosy_Bitterling_C", "Rosy Bitterling"},
    {"BP_Fish_Sardine_C", "Sardine"},
    {"BP_Fish_Scarlet_Koi_C", "Scarlet Koi"},
    {"BP_Fish_Shimmerfin_C", "Shimmerfin"},
    {"BP_Fish_SilverSalmon_C", "Silver Salmon"},
    {"BP_Fish_Silvery_Minnow_C", "Silvery Minnow"},
    {"BP_Fish_SmallmouthBass_C", "Smallmouth Bass"},
    {"BP_Fish_SpottedBullhead_C", "Spotted Bullhead"},
    {"BP_Fish_Stalking_Catfish_C", "Stalking Catfish"},
    {"BP_Fish_Stickleback_C", "Stickleback"},
    {"BP_Fish_Stonefish_C", "Stonefish"},
    {"BP_Fish_Stormray_C", "Stormray"},
    {"BP_Fish_StripedSturgeon_C", "Striped Sturgeon"},
    {"BP_Fish_Striped_Dace_C", "Striped Dace"},
    {"BP_Fish_Swordfin_Eel_C", "Swordfin Eel"},
    {"BP_Fish_Thundering_Eel_C", "Thundering Eel"},
    {"BP_Fish_UmbranCarp_C", "Umbran Carp"},
    {"BP_Fish_UnicornFish_C", "Unicorn Fish"},
    {"BP_Fish_Voidray_C", "Voidray"},
    {"BP_Fish_Willow_Lamprey_C", "Willow Lamprey"},
    {"BP_Fish_Yellowfin_Tuna_C", "Yellowfin Tuna"},
    {"BP_Fish_Yellow_Perch_C", "Yellow Perch"},
    {"BP_Trash_Shipfragments_C", "Ship Fragments"},
    {"BP_Trash_Wagonwheel_C", "Wagon Wheel"},
    {"BP_Trash_WaterloggedBoot_C", "Waterlogged Boot"},

    // NPCs (Villagers)
    { "BP_Villager_Miner_C", "Hodari" },
    { "BP_VillagerTheArchaeologist_C", "Jina" },
    { "BP_Villager_Cook_C", "Reth" },
    { "BP_Villager_Tish_C", "Tish" },
    { "BP_VillagerTheDemolitionist_C", "Najuma" },
    { "BP_Villager_Healer_C", "Chayne" },
    { "BP_Villager_Elouisa_C", "Elouisa" },
    { "BP_Villager_TheMagistrate_C", "Eshe" },
    { "BP_Villager_TheLibrarian_C", "Caleri" },
    { "BP_Villager_Tamala_C", "Tamala" },
    { "BP_Villager_Blacksmith_C", "Sifuu" },
    { "BP_Villager_Farmer_C", "Badruu" },
    { "BP_VillagerDeliveryBoy_C", "Auni" },
    { "BP_Villager_Farmboy_C", "Nai'o" },
    { "BP_Villager_Tau_C", "Tau" },
    { "BP_VillagerTheInnKeeper_C", "Ashura" },
    { "BP_Villager_Hekla_C", "Hekla" },
    { "BP_Villager_Zeki_C", "Zeki" },
    { "BP_Villager_Rancher_C", "Delaila" },
    { "BP_VillagerFisherman_C", "Einar" },
    { "BP_Villager_Kenyatta_C", "Kenyatta" },
    { "BP_Villager_Mayor_C", "Kenli" },
    { "BP_Villager_Jel_C", "Jel" },
    { "BP_VillagerTheHunter_C", "Hassian" },
    { "BP_VillagerTheWatcher_C", "Subira" },

    // Loot
    { "BP_Hunting_LootBag_C", "Animal Loot" },
    { "BP_InsectBallLoot_C", "Bug Loot" },
    { "BP_LootChestRockPile_C", "Stone Loot" },
    { "BP_LootChestClayPile_C", "Clay Loot" },
    { "BP_LootChestCopperPile_C", "Copper Loot" },
    { "BP_LootChestIronPile_C", "Iron Loot" },
    { "BP_LootChestPaliumPile_C", "Palium Loot" },
    { "BP_LootChestWoodBundle_Oak_C", "Sapwood Loot" },
    { "BP_LootChestWoodBundle_Birch_C", "Sapwood Loot" },
    { "BP_LootChestWoodBundle_Juniper_C", "Sapwood Loot" },
    { "BP_LootChestWoodBundle_Pine_C", "Heartwood Loot" },
    { "BP_LootChestWoodBundle_Enchanted_C", "Flow Loot" },

    { "BP_ChapaaPile_C", "Rummage Pile" },
    { "BP_BeachPile_C", "Rummage Pile" },

    // Treasure
    { "BP_ShinyPebble_Orange_C", "Shiny Orange Pebble" },
    { "BP_ShinyPebble_Yellow_C", "Shiny Yellow Pebble" },
    { "BP_ShinyPebble_Blue_C", "Shiny Blue Pebble" },
    { "BP_ShinyPebble_Green_C", "Shiny Green Pebble" },
    { "BP_ShinyPebble_Purple_C", "Shiny Purple Pebble" },
    { "BP_WorldPersistGatherable_Base_Small_C", "Bronze Treasure Chest" },
    { "BP_WorldPersistGatherable_Base_Med_C", "Silver Treasure Chest" },
    { "BP_WorldPersistGatherable_Base_Large_C", "Gold Treasure Chest" },
    { "BP_WorldPersistGatherable_Winterlights_C", "Winterlights Treasure Chest" },

    // Stables
    {"BP_Stables_Sign_C", "Stables - Fast Travel"},

    // TimedDrop
    {"BP_TimedDropDecoration_YoungSilverwingNest_C","Young Silverwing Nest"},
    {"BP_TimedDropDecoration_GaldurSeedMaker_C","Ancient Galdur Statue"},
    {"BP_TimedDropDecoration_KitsuuRockGarden_C","Ancient Rock Garden"},
};

// Search map for assigning loot bag type
inline std::map<ELootBagType, std::vector<std::string>> LOOT_TYPE_MAPPINGS = {
    {ELootBagType::Hunting, {"_Hunting_"}},
    {ELootBagType::Bug, {"_InsectBallLoot_"}},
    {ELootBagType::Mining, {"Pile_C"}},
    {ELootBagType::Chopping, {"WoodBundle_"}},
};

// Villager Textures
inline std::map<std::string, std::string> VillagerTextures = {
    {"BP_Villager_Miner_C", "/Game/UI/Icons_Characters/Hodari_Icon.Hodari_Icon"},
    {"BP_VillagerTheArchaeologist_C", "/Game/UI/Icons_Characters/Jina_Icon.Jina_Icon"},
    {"BP_Villager_Cook_C", "/Game/UI/Icons_Characters/Reth_icon.Reth_icon"},
    {"BP_Villager_Tish_C", "/Game/UI/Icons_Characters/Tish_Icon.Tish_Icon"},
    {"BP_VillagerTheDemolitionist_C", "/Game/UI/Icons_Characters/Najuma_Icon.Najuma_Icon"},
    {"BP_Villager_Healer_C", "/Game/UI/Icons_Characters/Chane_Icon.Chane_Icon"},
    {"BP_Villager_Elouisa_C", "/Game/UI/Icons_Characters/Elouisa_Icon1.Elouisa_Icon1"},
    {"BP_Villager_TheMagistrate_C", "/Game/UI/Icons_Characters/Eshe_Icon.Eshe_Icon"},
    {"BP_Villager_TheLibrarian_C", "/Game/UI/Icons_Characters/Calere_Icon.Calere_Icon"},
    {"BP_Villager_Tamala_C", "/Game/UI/Icons_Characters/Tamala_Icon.Tamala_Icon"},
    {"BP_Villager_Blacksmith_C", "/Game/UI/Icons_Characters/Sefu_Icon.Sefu_Icon"},
    {"BP_Villager_Farmer_C", "/Game/UI/Icons_Characters/Badru_Icon.Badru_Icon"},
    {"BP_VillagerDeliveryBoy_C", "/Game/UI/Icons_Characters/Auni_Icon.Auni_Icon"},
    {"BP_Villager_Farmboy_C", "/Game/UI/Icons_Characters/Nyo_Icon.Nyo_Icon"},
    {"BP_Villager_Tau_C", "/Game/UI/Icons/WT_Tau_portrait.WT_Tau_portrait"},
    {"BP_VillagerTheInnKeeper_C", "/Game/UI/Icons_Characters/Ashura_Icon.Ashura_Icon"},
    {"BP_Villager_Hekla_C", "/Game/UI/Icons_Characters/Hekla_Icon.Hekla_Icon"},
    {"BP_Villager_Zeki_C", "/Game/UI/Icons_Characters/Zeki_Icon.Zeki_Icon"},
    {"BP_Villager_Rancher_C", "/Game/UI/Icons_Characters/Dalila_Icon.Dalila_Icon"},
    {"BP_VillagerFisherman_C", "/Game/UI/Icons_Characters/Einar_Icon.Einar_Icon"},
    {"BP_Villager_Kenyatta_C", "/Game/UI/Icons_Characters/Kenyatta_Icon.Kenyatta_Icon"},
    {"BP_Villager_Mayor_C", "/Game/UI/Icons_Characters/Kenji_Icon.Kenji_Icon"},
    {"BP_Villager_Jel_C", "/Game/UI/Icons_Characters/Jel_Icon.Jel_Icon"},
    {"BP_VillagerTheHunter_C", "/Game/UI/Icons_Characters/Hassian_Icon.Hassian_Icon"},
    {"BP_VillagerTheWatcher_C", "/Game/UI/Icons/WT_Subira_Portrait.WT_Subira_Portrait"},
};

// Treasure Textures
inline std::map<std::string, std::string> TreasureTextures = {
    {"BP_ShinyPebble_Orange_C", "/Game/UI/Icons/Icon_ShinyPebble_orange.Icon_ShinyPebble_orange"},
    {"BP_ShinyPebble_Yellow_C", "/Game/UI/Icons/Icon_ShinyPebble_yellow.Icon_ShinyPebble_yellow"},
    {"BP_ShinyPebble_Blue_C", "/Game/UI/Icons/Icon_ShinyPebble_blue.Icon_ShinyPebble_blue"},
    {"BP_ShinyPebble_Green_C", "/Game/UI/Icons/Icon_ShinyPebble_green.Icon_ShinyPebble_green"},
    {"BP_ShinyPebble_Purple_C", "/Game/UI/Icons/Icon_ShinyPebble_purple.Icon_ShinyPebble_purple"},
    {"BP_WorldPersistGatherable_Base_Small_C", "/Game/UI/Icons/WT_Icon_Chest_Treasure_AncientHuman_Bronze.WT_Icon_Chest_Treasure_AncientHuman_Bronze"},
    {"BP_WorldPersistGatherable_Base_Med_C", "/Game/UI/Icons/WT_Icon_Chest_Treasure_AncientHuman_Silver.WT_Icon_Chest_Treasure_AncientHuman_Silver"},
    {"BP_WorldPersistGatherable_Base_Large_C", "/Game/UI/Icons/WT_Icon_Chest_Treasure_AncientHuman_Gold.WT_Icon_Chest_Treasure_AncientHuman_Gold"},
    {"BP_WorldPersistGatherable_Winterlights_C", "/Game/UI/Icons/WT_Icon_Chest_Treasure_Winterlights.WT_Icon_Chest_Treasure_Winterlights"},
    {"BP_WorldPersistGatherable_MajiMarket_C", "/Game/UI/Icons/Icon_Decor_MajiMarket_TreasureChest.Icon_Decor_MajiMarket_TreasureChest"},
};

/*
inline std::string BugTextures[static_cast<int>(EBugKind::MAX)][static_cast<int>(EBugQuality::MAX)] = {
    {}, // Unknown
    {   // Bee
        "", // Unknown
        "", // Common
        "/Game/UI/Icons/Icon_Bug_Bee_Bahari.Icon_Bug_Bee_Bahari", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Bee_GoldenGlory.Icon_Bug_Bee_GoldenGlory", // Rare
        "", // Rare2
        "", // Epic
    },
    {   // Beetle
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Beetle_SpottedStinkbug.Icon_Bug_Beetle_SpottedStinkbug", // Common
        "/Game/UI/Icons/Icon_Bug_Beetle_ProudhornedStag.Icon_Bug_Beetle_ProudhornedStag", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Beetle_Raspberry.Icon_Bug_Beetle_Raspberry", // Rare
        "", // Rare2
        "/Game/UI/Icons/Icon_Bug_Beetle_AncientAmber.Icon_Bug_Beetle_AncientAmber", // Epic
    },
    {   // Butterfly
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Butterfly_CommonBlue.Icon_Bug_Butterfly_CommonBlue", // Common
        "/Game/UI/Icons/Icon_Bug_Butterfly_Duskwing.Icon_Bug_Butterfly_Duskwing", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Butterfly_Brighteye.Icon_Bug_Butterfly_Brighteye", // Rare
        "", // Rare2
        "/Game/UI/Icons/Icon_Bug_Butterfly_RainbowTipped.Icon_Bug_Butterfly_RainbowTipped", // Epic
    },
    {   // Cicada
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Cicada_CommonBark.Icon_Bug_Cicada_CommonBark", // Common
        "/Game/UI/Icons/Icon_Bug_Cicada_Cerulean.Icon_Bug_Cicada_Cerulean", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Cicada_Spitfire.Icon_Bug_Cicada_Spitfire", // Rare
        "", // Rare2
        "", // Epic
    },
    {   // Crab
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Crab_Bahari.Icon_Bug_Crab_Bahari", // Common
        "/Game/UI/Icons/Icon_Bug_Crab_Spineshell.Icon_Bug_Crab_Spineshell", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Crab_Vampire.Icon_Bug_Crab_Vampire", // Rare
        "", // Rare2
        "", // Epic
    },
    {   // Cricket
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Cricket_CommonField.Icon_Bug_Cricket_CommonField", // Common
        "/Game/UI/Icons/Icon_Bug_Cricket_GardenLeafhopper.Icon_Bug_Cricket_GardenLeafhopper", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Cricket_AzureStonehopper.Icon_Bug_Cricket_AzureStonehopper", // Rare
        "", // Rare2
        "", // Epic
    },
    {   // Dragonfly
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Dragonfly_Brushtail.Icon_Bug_Dragonfly_Brushtail", // Common
        "/Game/UI/Icons/Icon_Bug_Dragonfly_Inky.Icon_Bug_Dragonfly_Inky", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Dragonfly_Firebreathing.Icon_Bug_Dragonfly_Firebreathing", // Rare
        "", // Rare2
        "/Game/UI/Icons/Icon_Bug_Dragonfly_Jewelwing.Icon_Bug_Dragonfly_Jewelwing", // Epic
    },
    {   // Glowbug
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Glowbug_PaperLantern.Icon_Bug_Glowbug_PaperLantern", // Common
        "", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Glowbug_Bahari.Icon_Bug_Glowbug_Bahari", // Rare
        "", // Rare2
        "", // Epic
    },
    {   // Ladybug
        "", // Unknown
        "", // Common
        "/Game/UI/Icons/Icon_Bug_Ladybug_Garden.Icon_Bug_Ladybug_Garden", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Ladybug_Princess.Icon_Bug_Ladybug_Princess", // Rare
        "", // Rare2
        "", // Epic
    },
    {   // Mantis
        "", // Unknown
        "", // Common
        "/Game/UI/Icons/Icon_Bug_Mantis_Garden.Icon_Bug_Mantis_Garden", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Mantis_Spotted.Icon_Bug_Mantis_Spotted", // Rare
        "/Game/UI/Icons/Icon_Bug_Mantis_Leafstalker.Icon_Bug_Mantis_Leafstalker", // Rare2
        "/Game/UI/Icons/Icon_Bug_Mantis_Fairy.Icon_Bug_Mantis_Fairy", // Epic
    },
    {   // Moth
        "", // Unknown
        "/Game/UI/Icons/Icon_Bug_Moth_KilimaNight.Icon_Bug_Moth_KilimaNight", // Common
        "/Game/UI/Icons/Icon_Bug_Moth_LunarFairy.Icon_Bug_Moth_LunarFairy", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Moth_GossamerVeil.Icon_Bug_Moth_GossamerVeil", // Rare
        "", // Rare2
        "", // Epic
    },
    {   // Pede
        "", // Unknown
        "", // Common
        "/Game/UI/Icons/Icon_Bug_Millipede_Garden.Icon_Bug_Millipede_Garden", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Millipede_Hairy.Icon_Bug_Millipede_Hairy", // Rare
        "/Game/UI/Icons/Icon_Bug_Millipede_Scintillating.Icon_Bug_Millipede_Scintillating", // Rare2
        "", // Epic
    },
    {   // Snail
        "", // Unknown
        "", // Common
        "/Game/UI/Icons/Icon_Bug_Snail_Garden.Icon_Bug_Snail_Garden", // Uncommon
        "/Game/UI/Icons/Icon_Bug_Snail_Stripeshell.Icon_Bug_Snail_Stripeshell", // Rare
        "", // Rare2
        "", // Epic
    },
};
*/

inline std::unordered_map<int32_t, std::pair<std::wstring, std::string>>TimedDropLoot = {
    // GaldurSeedMaker
    {20263, {L"Acorn", "/Game/UI/Icons/Icon_Seed_Acorn.Icon_Seed_Acorn"}},
    {220, {L"Flow Acorn", "/Game/UI/Icons/WT_Icon_Seed_Acorn_CoOp.WT_Icon_Seed_Acorn_CoOp"}},
    {31632, {L"Juniper Seed", "/Game/UI/Icons/Icon_Seed_Juniper.Icon_Seed_Juniper"}},
    {22297, {L"Flow Juniper Seed", "/Game/UI/Icons/WT_Icon_Seed_Juniper_CoOp.WT_Icon_Seed_Juniper_CoOp"}},
    {22034, {L"Pinecone", "/Game/UI/Icons/Icon_Seed_Pinecone.Icon_Seed_Pinecone"}},
    {743, {L"Flow Pinecone", "/Game/UI/Icons/WT_Icon_Seed_Pinecone_CoOp.WT_Icon_Seed_Pinecone_CoOp"}},
    {20333, {L"Samara", "/Game/UI/Icons/Icon_Seed_Samara.Icon_Seed_Samara"}},
    {17757, {L"Flow Samara", "/Game/UI/Icons/WT_Icon_Seed_Samara_CoOp.WT_Icon_Seed_Samara_CoOp"}},

    //YoungSilverwingNest
    {9935, {L"Blue Candy Egg", "/Game/UI/Icons/Icon_SilverwingEggBlue.Icon_SilverwingEggBlue"}},
    {19234, {L"Green Candy Egg", "/Game/UI/Icons/Icon_SilverwingEggGreen.Icon_SilverwingEggGreen"}},
    {5692, {L"Red Candy Egg", "/Game/UI/Icons/Icon_SilverwingEggRed.Icon_SilverwingEggRed"}},
    {4350, {L"Yellow Candy Egg", "/Game/UI/Icons/Icon_SilverwingEggYellow.Icon_SilverwingEggYellow"}},

    //KitsuuRockGarden
    {16272, {L"Spicy Pepper Seed", "/Game/UI/Icons/Icon_Seeds_Peppers.Icon_Seeds_Peppers"}},
    {30124, {L"Gold Ore", "/Game/UI/Icons/Icon_Ore_Gold.Icon_Ore_Gold"}},
    {10548, {L"Chapaa Meat", "/Game/UI/Icons/Icon_Steak_Chapaa.Icon_Steak_Chapaa"}},
    {29308, {L"Sernuk Meat", "/Game/UI/Icons/Icon_Steak_Cearnuk.Icon_Steak_Cearnuk"}},
    {30911, {L"Fur", "/Game/UI/Icons/Icon_Fur.Icon_Fur"}},
    {28732, {L"Sernuk Hide", "/Game/UI/Icons/Icon_Hide.Icon_Hide"}},
    {7159, {L"Fine Arrow", "/Game/UI/Icons/Icon_Ammo_ArrowIron.Icon_Ammo_ArrowIron"}},
    {31021, {L"Slowdown Arrow", "/Game/UI/Icons/Icon_Ammo_ArrowLethargy.Icon_Ammo_ArrowLethargy"}},
    {1538, {L"Dispel Arrow", "/Game/UI/Icons/Icon_Ammo_ArrowDispel.Icon_Ammo_ArrowDispel"}},
};

inline std::unordered_map<std::string, std::string>TeleporterMap = {
    // The Tower
    {"DA_BlackMarket_toDeveloperChallenge1","Black Market"},
    // Home
    {"DA_AZ1_FromHousingPlot","Bahari Bay"},
    {"DA_VillageRoot_HousingPlots","DO NOT USE"}, //"Kilima"},
    {"DA_HousingPlot_FromGreybox","Housing Plot"},
    // Black Market
    {"DA_VillageRoot_GeneralStore","Kilima - General Store"},
    {"DA_VillageRoot_Lake","Kilima - Crystal Lake"},
    {"DA_PS_RethRoom_2","Kilima - Reth's Storeroom"},
    {"DA_TeleportTravel_DeveloperChallenge1","The Tower"},
    {"DA_BMOfficeAddress","Zeki's Office"},
    // Kilima
    {"DA_HydroStationAddress", "DO NOT USE"},
    {"DA_CaleriRoom_VillageRoot", "Library Restricted Section"},
    {"DA_BlackMarket_toVillageRootLake", "Black Market - Crystal Lake Entrance"},
    {"DA_PS_EsheRoom", "Eshe's Bedroom"},
    {"DA_PS_KenyattaRoom", "Kenyatta's Bedroom"},
    {"DA_ChanesRoom_VillageRoot", "Chayne's Bedroom"},
    {"DA_PS_SubiraInn", "Subira's Room"},
    {"DA_PS_ZekiRoom", "Zeki's Bedroom"},
    {"DA_PS_KenliRecordsRoom", "Kenli's Records Room"},
    {"DA_PS_ElouisaRoom", "Elouisa's Bedroom"},
    {"DA_PS_SifuuRoom", "Sifuu's Bedroom"},
    {"DA_PS_JinaLibrary", "Ancient Library"},
    {"DA_PS_HeklaTent", "Hekla's Tent"},
    {"DA_PS_BadruuBarn", "Badruu's Barn"},
    {"DA_NightSkyTemple_Entrance", "Night Sky Temple"},
    {"DA_PS_AuniTreehouse", "Auni's Treehouse"},
    {"DA_PS_NaioROom", "Nai'o and Auni's Bedroom"},
    {"DA_PS_DelailaRoom", "Dalaila and Badruu's Bedroom"},
    {"DA_PS_EinarCave", "Einar's Cave"},
    {"DA_WaterShrine_Entrance", "Water Shrine"},
    {"DA_VillageRoot_fromCItyHallStoreRoom", "City Hall Storage Room"},
    {"DA_BlackMarket_toGeneralStore", "Black Market - General Store Entrance"},
    {"DA_VillageRoot_toCItyHallStoreRoom", "City Hall Outside Storage Room"},
    {"DA_PS_TishRoom", "Tish's Bedroom"},
    {"DA_PS_RethRoom", "Reth's Storeroom"},
    {"DA_PS_AshuraRoom", "Ashura's Room"},
    {"DA_PS_JelRoom", "Jel's Bedroom"},
    {"DA_VillageRoot_SouthEastGate", "Kilima - Fairground's Entrance"},
    {"DA_FairGrounds_North", "Fairgrounds"},
    {"DA_AZ1_FromVillage", "Bahari"},
    {"DA_HousingPlot", "Home"},
    {"DA_BlackMarket_toPSRethStoreroom", "Black Market - Reth's Storeroom Entrance"},
    {"DA_VillageRoot_toPSRethStoreroom", "Kilima - Outside Reth's Storeroom"},
    // Bahari
    {"DA_PS_LighthouseBasement", "Lighthouse Basement"},
    {"DA_CollapsedMineshaft_Interior", "Northern Mineshaft"},
    {"DA_AeroStationAddress", "DO NOT USE"},
    {"DA_PS_TamalaBedroom", "Tamala's Bedroom"},
    {"DA_AZ1toAirTemple", "Air Temple"},
    {"DA_PyroStationAddress", "DO NOT USE"},
    {"DA_EarthTempleAddress", "DO NOT USE"},
    {"DA_PS_HassianGrove", "Hassian's Grove"},
    {"DA_FireTemple_Entrance", "Fire Temple"},
    {"DA_PS_HodariBedroom", "Hodari's Bedroom"},
    {"DA_PS_NajumaBedroom", "Najuma's Bedroom"},
    {"DA_VillageRoot_EastGate", "Kilima"},
    {"DA_HousingPlot_ShortCut", "Home"},
    {"DA_Teleport_AZ2_Elderwood_ToBahari", "Elderwood"},
    // Fire Temple
    // Earth Temple
    // Air Temple
    // Elderwood
    {"DA_AZ1_FromElderwood", "Bahari"},
};

enum EValeriaLevel : uint8_t {
    UnknownLvl = 0,
    Home = 1 << 0,
    Kilima = 1 << 1,
    Bahari = 1 << 2,
    Elderwood = 1 << 3,
    BlackMarket = 1 << 4,
    Tower = 1 << 5,
    MajiMarket = 1 << 6,
    Lobby = 1 << 7,
    Startup = Lobby | UnknownLvl,
};
UE_ENUM_OPERATORS(EValeriaLevel)

static inline std::unordered_map<EValeriaLevel, std::string> EValeriaLevelString = {
    {EValeriaLevel::UnknownLvl,"Unknown"},
    {EValeriaLevel::Home,"Housing Plot"},
    {EValeriaLevel::Kilima,"Kilima Valley"},
    {EValeriaLevel::Bahari,"Bahari Bay"},
    {EValeriaLevel::Elderwood,"Elderwood"},
    {EValeriaLevel::BlackMarket,"The Underground"},
    {EValeriaLevel::Tower,"The Tower"},
    {EValeriaLevel::MajiMarket,"Maji Market"},
    {EValeriaLevel::Lobby,"Lobby"},
};

static inline std::unordered_map<std::string, EValeriaLevel> EValeriaLevelMap = {
    {"DeveloperChallenge1", EValeriaLevel::Tower},
    {"PublicHousingPlot_Root", EValeriaLevel::Home},
    {"Village_MajiMarket_01_Root", EValeriaLevel::MajiMarket},
    {"Fairgrounds_MajiMarket_02_LNY_WP_Root", EValeriaLevel::MajiMarket},
    {"Fairgrounds_MajiMarket_03_626_WP_Root", EValeriaLevel::MajiMarket},
    {"Village_Fairgrounds_Root", EValeriaLevel::MajiMarket},
    {"Village_Root", EValeriaLevel::Kilima},
    {"AZ1_01_Root", EValeriaLevel::Bahari},
    {"AZ2_Root", EValeriaLevel::Elderwood},
    {"Village_Black_Market_Root", EValeriaLevel::BlackMarket},
    {"MAP_PreGame",EValeriaLevel::Lobby},
};


using namespace SDK;

class ActorHandler
{
public:
    static void Start();
    static void Stop();

    static void SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC);
    static void ClientTravelInternal(const UObject* Context, UFunction* Function, void* Parms);

    static inline EValeriaLevel CurrentMap = EValeriaLevel::UnknownLvl;
    static inline ULevel* CurrentLevel = nullptr;
    static void Tick(const UObject* Context, UFunction* Function, void* Parms);

    static void Func_OnRep_ActiveVariants(void* Context, void* TheStack, void* Result);

    static void ProcessActor(AActor*);
    static void ProcessBPActor(AActor*);
    static std::map<std::string, AActor*>GetTeleporters(const AValeriaCharacter*);
    static bool IsBlueprintClass(UClass*);
    static bool IsActorA(const AActor*, const std::wstring&);
    static void FinishProcessingActor(AActor*, EType);
    static void RemoveActor(AActor*);
    static void UpdateActors();
    static void UpdateDespawn();
    static UClass* ClassLookup(std::wstring);
    static void AddClass(UClass*);
    static void RemoveClass(UClass*);
    static UTexture2D* TextureLookup(const std::string& texture);
    static std::vector<std::shared_ptr<FEntry>>GetActors();
    static std::vector<std::shared_ptr<FEntry>>GetActorsOfType(EType);

    static inline bool bListenersAdded = false;
private:

    static inline std::vector<std::pair<std::wstring, EType>>BPActors = {
        {L"/Game/Core/BP_Valeria_Gatherable_Placed.BP_Valeria_Gatherable_Placed", EType::Forage},
        {L"/Game/Core/BP_Loot.BP_Loot", EType::Loot},
        {L"/Game/Gameplay/Architecture/_Generic/Stables/BP_Stables_FrontGate_01.BP_Stables_FrontGate_01", EType::Gates},
        {L"/Game/Gameplay/Architecture/_Generic/Stables/BP_Stables_FrontGate_02.BP_Stables_FrontGate_02", EType::Gates},
        {L"/Game/Gameplay/Stables/BP_Stables_Sign.BP_Stables_Sign", EType::Stables},
        {L"/Game/Gameplay/QuestItems/baseClass/BP_QuestItem_BASE.BP_QuestItem_BASE", EType::Quest},
        {L"/Game/Gameplay/Inspectables/Base/BP_SimpleInspect_Base.BP_SimpleInspect_Base", EType::Quest},
        {L"/Game/Gameplay/Inspectables/Base/BP_QuestInspect_Base.BP_QuestInspect_Base", EType::Quest},
        {L"/Game/Gameplay/Housing/Decorations/TimedDropDecorations/BP_TimedDropDecoration_Base.BP_TimedDropDecoration_Base", EType::TimedDrop},
        {L"/Game/Gameplay/Skills/Fishing/Shared/BP_Minigame_Fish.BP_Minigame_Fish", EType::Fish},
        {L"/Game/Environment/Water/BP_WaterPlane_Fishing_Base_SQ.BP_WaterPlane_Fishing_Base_SQ", EType::Pool},
        {L"/Game/Gameplay/Books/BP_ConfigurableBook.BP_ConfigurableBook", EType::Relic},
        {L"/Game/Core/BP_Valeria_Shop_Gatherable.BP_Valeria_Shop_Gatherable", EType::Shops},
        {L"/Game/Core/BP_ValeriaGatherable.BP_ValeriaGatherable", EType::Other}
    };

    //static inline std::unordered_map<std::string, UTexture2D*>TexturePtrMap = {};
    static inline std::unordered_map<std::wstring, UClass*>ClassPtrMap = {};
    //static inline std::deque<std::pair<AActor*, EType>>ActorQueue = {};
    //static inline std::deque<AActor*>BPActorQueue = {};
    static inline std::vector<std::shared_ptr<FEntry>>ActorCache = {};
    static inline bool bIsTraveling = false;
    static inline double LastUpdate = 0;
    static inline double LastDormantUpdate = 0;
    static inline std::vector<AActor*>Teleporters = {};

    static inline std::mutex ActorCacheMutex;

    static inline FGameplayTag FlowtreeTag = {};
    static inline FGameplayTag StarQualityTag = {};
    static inline FGameplayTag InfectedTag = {};

public:

};