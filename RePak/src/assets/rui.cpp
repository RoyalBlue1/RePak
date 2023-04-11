#include "pch.h"
#include "Assets.h"
#include <dxutils.h>

union defaultValue {
    int asInt;
    float asFloat;
    uint64_t asInt64;
    float asVec2D[2];
    float asVec3D[3];
    float asVec4D[4];
};
struct RuiConstValueProto {
    RuiArgumentType_t type;
    uint32_t valueOffset;
    defaultValue value;
    std::string stringValue;
};
struct RuiArgumentProto {
    std::string name;
    RuiArgumentType_t type;
    defaultValue value;
    std::string stringValue;
    uint32_t valueOffset;
    uint32_t nameOffset;
    uint16_t shortHash;
};
enum ProtoValueFlags {
    PVF_RUNTIMEVAL = 1 << 0,
};
struct ProtoValue {
    int offset = 0;
    std::string name;
    RuiArgumentType_t type;
    std::string stringVal;
    defaultValue val;
    int flags;
};

struct unknown8dataProto
{
    uint16_t type;
    uint16_t fontIndex;
    ProtoValue color0_red;
    ProtoValue color0_green;
    ProtoValue color0_blue;
    ProtoValue color0_alpha;//probably alpha
    ProtoValue color1_red;
    ProtoValue color1_green;
    ProtoValue color1_blue;
    ProtoValue color1_alpha;
    ProtoValue color2_red;
    ProtoValue color2_green;
    ProtoValue color2_blue;
    ProtoValue color2_alpha;
    ProtoValue Val_1A;
    ProtoValue Val_1C;
    ProtoValue Val_1E;
    ProtoValue Val_20;
    ProtoValue Val_22;
    ProtoValue Val_24;
    ProtoValue Val_26;
    ProtoValue Val_28;
    ProtoValue Val_2A;
    ProtoValue Val_2C;
    ProtoValue Val_2E;
    ProtoValue Val_30;
    ProtoValue Val_32;

};

struct unknown9Proto {
    uint16_t type;
    std::string name;
    int transform_Index;
    int unk8Index_0;
    int unk8Index_1;
    int unk8Index_2;
    int unk8Index_3;
    ProtoValue Val_4;
    ProtoValue Val_6;
    ProtoValue Val_8;
    ProtoValue Val_A;
    ProtoValue Val_C;
    ProtoValue Val_E;
    ProtoValue Val_10;
    ProtoValue Val_12;
    ProtoValue Val_14;
    ProtoValue Val_16;
    ProtoValue Val_18;
    ProtoValue Val_1A;
    ProtoValue Val_1C;
    ProtoValue Val_1E;
    ProtoValue Val_20;
    ProtoValue Val_22;
    ProtoValue Val_24;
    uint16_t word;
};

struct transformSubProto {
    uint16_t transformIndex;
    uint16_t someIndex;
    uint16_t iVal_1;
    ProtoValue Val_0;
    ProtoValue Val_1;
    ProtoValue Val_2;
    ProtoValue Val_3;
    ProtoValue Val_4;
    ProtoValue Val_5;
    ProtoValue Val_6;
    ProtoValue Val_7;
    ProtoValue Val_8;
    ProtoValue Val_9;
    ProtoValue Val_10;
    ProtoValue Val_11;
    ProtoValue Val_12;
};

struct transformProto {
    uint16_t type;
    uint16_t count;
    std::vector<transformSubProto> subProtos;
};

struct DynamicValueProto {
    RuiArgumentType_t type;
    std::string name;
    int offset;
};

struct unknown8dataStruct
{
    uint16_t type;
    uint16_t word_2;
    uint16_t word_4;
    uint16_t word_6;
    uint16_t word_8;
    uint16_t word_A;
    uint16_t word_C;
    uint16_t word_E;
    uint16_t word_10;
    uint16_t word_12;
    uint16_t word_14;
    uint16_t word_16;
    uint16_t word_18;
    uint16_t word_1A;
    uint16_t word_1C;
    uint16_t word_1E;
    uint16_t word_20;
    uint16_t word_22;
    uint16_t word_24;
    uint16_t word_26;
    uint16_t word_28;
    uint16_t word_2A;
    uint16_t word_2C;
    uint16_t word_2E;
    uint16_t word_30;
    uint16_t word_32;
};

struct unknown9dataStruct_0
{
    uint16_t type;
    uint16_t transformIndex;
    uint8_t uint8_4;
    uint8_t uint8_5;
    uint8_t uint8_6;
    uint8_t uint8_7;
    uint16_t textOffset;
    uint16_t uint16_A;
    uint16_t uint16_C;
    uint16_t uint16_E;
    uint16_t uint16_10;
};

struct __declspec(align(1)) unknown9dataStruct_1
{
    uint16_t type;
    uint16_t transformIndex;
    uint16_t uint16_4;
    uint16_t uint16_6;
    uint16_t uint16_8;
    uint16_t uint16_A;
    uint16_t uint16_C;
    uint16_t uint16_E;
    uint16_t uint16_10;
    uint16_t uint16_12;
    uint16_t uint16_14;
    uint16_t uint16_16;
    uint16_t uint16_18;
    uint16_t uint16_1A;
    uint16_t uint16_1C;
    uint16_t uint16_1E;
    uint16_t uint16_20;
    uint16_t uint16_22;
    uint16_t uint16_24;
    uint16_t word_26;
    uint8_t uint8_28;
    char pad_29 = 0;
};

struct unknown9dataStruct_2
{
    uint16_t type;
    uint16_t transformIndex;
    uint16_t uint16_4;
    uint16_t uint16_6;
    uint16_t uint16_8;
    uint16_t uint16_A;
    uint16_t uint16_C;
    uint16_t uint16_E;
    uint16_t uint16_10;
    uint16_t uint16_12;
    uint16_t uint16_14;
    WORD word_16;
    uint8_t uint8_18;
    char pad_19 = 0;
};


//TODO support more types
//only string like and int and float are supported
void setConstOffets(std::vector<RuiConstValueProto>& constants, ProtoValue& val) {
    if(val.type == TYPE_FLOAT || val.type == TYPE_INT || val.type == TYPE_BOOL) {
        for (auto& con : constants) {
            if (con.value.asInt == val.val.asInt) {
                val.offset = con.valueOffset;
                return;
            }
        }
    }
    int offset = 0;
    for (auto& con : constants) {
        if(val.type == TYPE_FLOAT || val.type == TYPE_INT || val.type == TYPE_BOOL) {
            offset += 4;
        }
        else {
            offset += 8;
        }
    }
    RuiConstValueProto proto;
    proto.value = val.val;
    proto.stringValue = val.stringVal;
    proto.valueOffset = offset;
    proto.type = val.type;
    constants.push_back(proto);
    val.offset = offset;
}

ProtoValue getJsonFloatValue(rapidjson::Value& jsonObj,std::string valName, float defaultVal, std::vector<RuiConstValueProto> &constants) {
    ProtoValue val;
    val.type = TYPE_FLOAT;
    if (jsonObj.HasMember((valName + "_name").c_str()) && jsonObj[(valName + "_name").c_str()].IsString()) {
        val.name = jsonObj[(valName+ "_name").c_str()].GetString();
        val.flags |= PVF_RUNTIMEVAL;
        return val;
    }
        

    val.val.asFloat = defaultVal;
    if (jsonObj.HasMember(valName.c_str())){
        if (jsonObj[valName.c_str()].IsNumber()) {
            val.val.asFloat = jsonObj[valName.c_str()].GetFloat();
        }
        
    }
    setConstOffets(constants,val);
    return val;
}

ProtoValue getJsonIntValue(rapidjson::Value& jsonObj,std::string valName, int defaultVal, std::vector<RuiConstValueProto> &constants) {
    ProtoValue val;
    val.type = TYPE_INT;
    if (jsonObj.HasMember((valName + "_name").c_str()) && jsonObj[(valName + "_name").c_str()].IsString()) {
        val.name = jsonObj[(valName+ "_name").c_str()].GetString();
        val.flags |= PVF_RUNTIMEVAL;
        return val;
    }


    val.val.asInt = defaultVal;
    if (jsonObj.HasMember(valName.c_str()) && jsonObj[valName.c_str()].IsInt()) {
        val.val.asInt =  jsonObj[valName.c_str()].GetInt();
        
    }
    setConstOffets(constants,val);
    return val;
}

ProtoValue getJsonStringValue(rapidjson::Value& jsonObj,std::string valName,std::string defaultVal, std::vector<RuiConstValueProto> &constants,size_t& constSize) {
    ProtoValue val;
    val.type = TYPE_STRING;
    if (jsonObj.HasMember((valName + "_name").c_str()) && jsonObj[(valName + "_name").c_str()].IsString()) {
        val.name = jsonObj[(valName+ "_name").c_str()].GetStdString();
        val.flags |= PVF_RUNTIMEVAL;
        return val;
    }


    val.stringVal = defaultVal;
    if (jsonObj.HasMember(valName.c_str()) && jsonObj[valName.c_str()].IsInt()) {
        val.stringVal =  jsonObj[valName.c_str()].GetStdString();
        constSize += val.stringVal.size() +1;
    }
    setConstOffets(constants,val);
    return val;
}


void setDynamicOffset(std::vector<RuiArgumentProto>& arguments,std::vector<DynamicValueProto>& dynamicValues,size_t& dynamicValuesSize,size_t valuesSize,ProtoValue& val) {
    if(val.name.size()==0)
        return;
    for (auto& arg : arguments) {
        if (arg.name == val.name) {
            if(arg.type != val.type)
                Error("Type mismatch when trying to set value from arg");
            val.offset = arg.valueOffset;
            return;
        }
    }
    for (auto& dynamicVal : dynamicValues) {
        if (dynamicVal.name == val.name) {
            if(dynamicVal.type != val.type)
                Error("Type mismatch when trying to set value from dynamicValue");
            val.offset = dynamicVal.offset;
            return;
        }
    }
    DynamicValueProto dynamicVal;
    if (val.type == TYPE_STRING || val.type == TYPE_ASSET || val.type == TYPE_UIHANDLE) {
        if(dynamicValuesSize%8)
            dynamicValuesSize += 8 - ( dynamicValuesSize % 8 );
    }
    dynamicVal.name = val.name;
    dynamicVal.type = val.type;
    dynamicVal.offset = dynamicValuesSize + valuesSize;
    val.offset = dynamicValuesSize + valuesSize;
    dynamicValues.push_back(dynamicVal);

    dynamicValuesSize += ruiArgSizeFromType[val.type];

}

uint32_t calculateShortHash(const char* name,uint32_t mul,uint32_t add){
    uint32_t i = 0;
    uint32_t hash = 0;
    while(name[i]){
        hash *= mul;
        hash += add + name[i];
        i++;
    }
    hash = hash ^ (hash >> 4);
    return hash;
    //shorthash = (unsigned short)(hash>>4);
    //posistion in array = (cluster.argIndex + (hash & (cluster.argCount -1)));
}

void calculateHashVars(RuiArgCluster& cluster, std::vector<RuiArgumentProto> &args) {
    for (int add = 0; add < 256; add++) {
        for (int mul = 1; mul < 256; mul++) {
            bool success = true;
            std::vector<bool> argSlots(cluster.argCount,false);
            for (auto& arg : args) {
                uint32_t argIndex = calculateShortHash(arg.name.c_str(),mul,add) & (cluster.argCount -1);
                if (argSlots[argIndex]) {
                    success = false;
                    break;
                }
                argSlots[argIndex] = true;
            }
            if (success) {
                cluster.byte1 = mul;
                cluster.byte2 = add;
                return;
            }
        }
        
    }
}

void Assets::AddRuiAsset(CPakFile* pak, std::vector<RPakAssetEntry>* assetEntries, const char* assetPath, rapidjson::Value& mapEntry)
{
    Log("Adding rui asset '%s'\n", assetPath);

    // data segment order:
    // name
    // values
    // default string values
    // transformFuncs
    // unk8 stuff
    // unk9 stuff
    // argClusters
    // args
    // unk10 data
    // unk10 subdata

    // create the segment for the subheader
    _vseginfo_t subhdrinfo = pak->CreateNewSegment(sizeof(RuiHeader), SF_HEAD | SF_CLIENT, 8);
    // make the subheader
    RuiHeader* pHdr = new RuiHeader();

    ////////////////
    // ASSET NAME
    // the asset name, without the file extension or anything like that
    std::string name = std::filesystem::path(assetPath).stem().string();
    // create a buffer for the name segment
    char* namebuf = new char[name.size() + 1];
    memmove(namebuf,  name.c_str(),name.size());
    namebuf[name.size()] = '\0';
    Log("-> asset name: '%s'\n", namebuf);

    // create the segment for the name
    _vseginfo_t assetNameInfo{};
    assetNameInfo = pak->CreateNewSegment(name.size() + 1, SF_CLIENT | SF_CPU, 1);

    ////////////////////////////
    // ASSET CONSTS/ARGS/VARS

    // GET THE SIZE OF THE STRUCT AND VALUES

    size_t constsSize = 0;
    size_t constStringsSize = 0;
    size_t nameStringsSize = 0;
  
    size_t varsSize = 0;  
    size_t dynamicValuesSize = 0;
    size_t argsSize = 0;

    size_t unknown9Size = 0;
    size_t transformSize = 0;

    std::vector<RuiArgumentProto>  argumentPrototypes;
    std::vector<RuiConstValueProto> constValueProtos;
    std::vector<unknown8dataProto> unknown8Prototypes;
    std::vector<unknown9Proto> unknown9Prototypes;
    std::vector<transformProto> transformPrototypes;
    std::vector<DynamicValueProto> dynamicValuePrototypes;

    ProtoValue zeroVal;
    zeroVal.type = TYPE_FLOAT;
    zeroVal.val.asFloat = 0;
    setConstOffets(constValueProtos,zeroVal);
    
    for (auto& it : mapEntry["styleDescriptors"].GetArray()) {
        unknown8dataProto unk;
        //memset(&unk,0,sizeof(unk));
        unk.type = it["type"].GetInt();
        switch(unk.type){
        case 0://font
            unk.color0_red = getJsonFloatValue(it,"color0Red",1,constValueProtos);
            unk.color0_green = getJsonFloatValue(it,"color0Green",1,constValueProtos);
            unk.color0_blue = getJsonFloatValue(it,"color0Blue",1,constValueProtos);
            unk.color0_alpha = getJsonFloatValue(it,"color0Alpha",1,constValueProtos);
            unk.color1_red = getJsonFloatValue(it,"color1Red",0,constValueProtos);
            unk.color1_green = getJsonFloatValue(it,"color1Green",0,constValueProtos);
            unk.color1_blue = getJsonFloatValue(it,"color1Blue",0,constValueProtos);
            unk.color1_alpha = getJsonFloatValue(it,"color1Alpha",0,constValueProtos);
            unk.color2_red = getJsonFloatValue(it,"color2Red",0,constValueProtos);
            unk.color2_green = getJsonFloatValue(it,"color2Green",0,constValueProtos);
            unk.color2_blue = getJsonFloatValue(it,"color2Blue",0,constValueProtos);
            unk.color2_alpha = getJsonFloatValue(it,"color2Alpha",0,constValueProtos);
            unk.Val_1A = getJsonFloatValue(it,"val_1A",1,constValueProtos);
            unk.Val_1C = getJsonFloatValue( it,"val_1C",1,constValueProtos);
            unk.fontIndex = it["fontIndex"].GetInt();
            unk.Val_20 = getJsonFloatValue(it,"val_20",0,constValueProtos);
            unk.Val_22 = getJsonFloatValue(it,"val_22",0,constValueProtos);
            unk.Val_24 = getJsonFloatValue(it,"val_24",0,constValueProtos);
            unk.Val_26 = getJsonFloatValue(it,"val_26",0,constValueProtos);
            unk.Val_28 = getJsonFloatValue(it,"textSize",10,constValueProtos);//text size
            unk.Val_2A = getJsonFloatValue(it,"stretchX",1,constValueProtos);//x stretch
            unk.Val_2C = getJsonFloatValue(it,"backgroundSize",0,constValueProtos);//background size
            unk.Val_2E = getJsonFloatValue(it,"boltness",0,constValueProtos);//boltness
            unk.Val_30 = getJsonFloatValue(it,"blur",0,constValueProtos);//blur
            break;
        case 1:
            unk.color0_red = getJsonFloatValue(it,"val_2",1,constValueProtos);
            unk.color0_green = getJsonFloatValue(it,"val_4",1,constValueProtos);
            unk.color0_blue = getJsonFloatValue(it,"val_6",1,constValueProtos);
            unk.color0_alpha = getJsonFloatValue(it,"val_8",1,constValueProtos);
            unk.color1_red = getJsonFloatValue(it,"val_A",0,constValueProtos);
            unk.color1_green = getJsonFloatValue(it,"val_C",0,constValueProtos);
            unk.color1_blue = getJsonFloatValue(it,"val_E",0,constValueProtos);
            unk.color1_alpha = getJsonFloatValue(it,"val_10",1,constValueProtos);
            unk.color2_red = getJsonFloatValue(it,"val_12",1,constValueProtos);
            unk.color2_green = getJsonFloatValue(it,"val_14",1,constValueProtos);
            unk.color2_blue = getJsonFloatValue(it,"val_16",1,constValueProtos);
            unk.color2_alpha = getJsonFloatValue(it,"val_18",1,constValueProtos);
            unk.Val_1A = getJsonFloatValue(it,"val_1A",0,constValueProtos);
            unk.Val_1C = getJsonFloatValue( it,"val_1C",0,constValueProtos);
            unk.Val_1E = getJsonFloatValue(it, "val_1E", 0, constValueProtos);
            unk.Val_20 = getJsonFloatValue(it, "val_20", 0, constValueProtos);
            unk.Val_22 = getJsonFloatValue(it, "val_22", 0, constValueProtos);
            unk.Val_24 = getJsonFloatValue(it, "val_24", 0, constValueProtos);
            unk.Val_26 = getJsonFloatValue(it, "val_26", 0, constValueProtos);
            unk.Val_28 = getJsonFloatValue(it, "val_28", 0, constValueProtos);
            unk.Val_2A = getJsonFloatValue(it, "val_2A", 0, constValueProtos);
            unk.Val_2C = getJsonFloatValue(it,"val_2C",0,constValueProtos);
            unk.Val_2E = getJsonFloatValue(it,"val_2E",0,constValueProtos);
            unk.Val_30 = getJsonFloatValue(it,"val_30",0,constValueProtos);
            break;
        case 2:
            unk.color0_red = getJsonFloatValue(it, "val_2", 1, constValueProtos);
            unk.color0_green = getJsonFloatValue(it, "val_4", 1, constValueProtos);
            unk.color0_blue = getJsonFloatValue(it, "val_6", 1, constValueProtos);
            unk.color0_alpha = getJsonFloatValue(it, "val_8", 1, constValueProtos);
            unk.color1_red = getJsonFloatValue(it, "val_A", 0, constValueProtos);
            unk.color1_green = getJsonFloatValue(it, "val_C", 0, constValueProtos);
            unk.color1_blue = getJsonFloatValue(it, "val_E", 0, constValueProtos);
            unk.color1_alpha = getJsonFloatValue(it, "val_10", 0, constValueProtos);
            unk.color2_red = getJsonFloatValue(it, "val_12", 0, constValueProtos);
            unk.color2_green = getJsonFloatValue(it, "val_14", 0, constValueProtos);
            unk.color2_blue = getJsonFloatValue(it, "val_16", 0, constValueProtos);
            unk.color2_alpha = getJsonFloatValue(it, "val_18", 0, constValueProtos);
            unk.Val_1A = getJsonFloatValue(it, "val_1A", 0, constValueProtos);
            unk.Val_1C = getJsonFloatValue(it, "val_1C", 0, constValueProtos);
            unk.Val_1E = getJsonFloatValue(it, "val_1E", 0, constValueProtos);
            unk.Val_20 = getJsonFloatValue(it, "val_20", 0, constValueProtos);
            unk.Val_22 = getJsonFloatValue(it, "val_22", 0, constValueProtos);
            unk.Val_24 = getJsonFloatValue(it, "val_24", 0, constValueProtos);
            unk.Val_26 = getJsonFloatValue(it, "val_26", 0, constValueProtos);
            unk.Val_28 = getJsonFloatValue(it, "val_28", 0, constValueProtos);
            unk.Val_2A = getJsonFloatValue(it, "val_2A", 0, constValueProtos);
            break;
        }
        unknown8Prototypes.push_back(unk);
    }

    for (auto& it : mapEntry["unk9"].GetArray()) {
        unknown9Proto unk;
        //memset(&unk,0,sizeof(unk));
        unk.type = it["type"].GetInt();
        unk.transform_Index = it["transformIndex"].GetInt();
        unk.unk8Index_0 = it["unk8Index"].GetInt();

        switch (unk.type) {
        case 0:
            unk.unk8Index_1 = it["unk8Index_1"].GetInt();
            unk.unk8Index_2 = it["unk8Index_2"].GetInt();
            unk.unk8Index_3 = it["unk8Index_3"].GetInt();
            unk.Val_8 = getJsonStringValue(it,"printString","ERROR",constValueProtos,constStringsSize);
            unk.Val_A = getJsonFloatValue(it,"val_A",1000000000.000000,constValueProtos);
            unk.Val_C = getJsonFloatValue( it,"val_C",1000000000.000000,constValueProtos);
            unk.Val_E = getJsonFloatValue(it,"val_E",0,constValueProtos);
            unk.Val_10 = getJsonFloatValue(it,"val_10",0,constValueProtos);
            
            unknown9Size += 0x12;
            break;
        case 1:
            unk.Val_4 = getJsonIntValue(it,"val_4",2,constValueProtos);
            unk.Val_6 = getJsonIntValue(it,"val_6",-1,constValueProtos);
            unk.Val_8 = getJsonFloatValue(it,"val_8",0,constValueProtos);
            unk.Val_A = getJsonFloatValue(it,"val_A",0,constValueProtos);
            unk.Val_C = getJsonFloatValue( it,"val_C",1,constValueProtos);
            unk.Val_E = getJsonFloatValue(it,"val_E",1,constValueProtos);
            unk.Val_10 = getJsonFloatValue(it,"val_10",0,constValueProtos);
            unk.Val_12 = getJsonFloatValue(it,"val_12",0,constValueProtos);
            unk.Val_14 = getJsonFloatValue(it,"val_14",1,constValueProtos);
            unk.Val_16 = getJsonFloatValue(it,"val_16",1,constValueProtos);
            unk.Val_18 = getJsonFloatValue(it,"val_18",0,constValueProtos);
            unk.Val_1A = getJsonFloatValue(it,"val_1A",0,constValueProtos);
            unk.Val_1C = getJsonFloatValue( it,"val_1C",0,constValueProtos);
            unk.Val_1E = getJsonFloatValue(it,"val_1E",0,constValueProtos);
            unk.Val_20 = getJsonFloatValue(it,"val_20",0,constValueProtos);
            unk.Val_22 = getJsonFloatValue(it,"val_22",0,constValueProtos);
            unk.Val_24 = getJsonFloatValue( it,"val_24",0,constValueProtos);
            unk.word = 0x1000;
            if(it.HasMember("word")&&it["word"].IsInt())
                unk.word = it["word"].GetInt();
            unknown9Size += 0x2A;
            break;
        case 2:
            unk.Val_4 = getJsonIntValue(it,"val_4",0,constValueProtos);
            unk.Val_6 = getJsonFloatValue(it,"val_6",0,constValueProtos);
            unk.Val_8 = getJsonFloatValue(it,"val_8",0,constValueProtos);
            unk.Val_A = getJsonFloatValue(it,"val_A",1,constValueProtos);
            unk.Val_C = getJsonFloatValue( it,"val_C",1,constValueProtos);
            unk.Val_E = getJsonFloatValue(it,"val_E",0,constValueProtos);
            unk.Val_10 = getJsonFloatValue(it,"val_10",0,constValueProtos);
            unk.Val_12 = getJsonFloatValue(it,"val_12",1,constValueProtos);
            unk.Val_14 = getJsonFloatValue(it,"val_14",1,constValueProtos);
            unk.word = 0x2000;
            if(it.HasMember("word")&&it["word"].IsInt())
                unk.word = it["word"].GetInt();
            unknown9Size += 0x1A;
            break;
        }
        unknown9Prototypes.push_back(unk);
    }

    for (auto& it : mapEntry["transforms"].GetArray()) {
        transformProto transProto;
        if (!it.HasMember("type") || !it["type"].IsInt()) {
            continue;
        }
        transProto.type = it["type"].GetInt();

        switch (transProto.type) {
        case 0:
            transformSize += 1;
            break;

        case 1:
            
            transProto.count = 0;
            if(it.HasMember("data")&&it["data"].IsArray())
                transProto.count = it["data"].GetArray().Size();
            transformSize += 2 + transProto.count* 2;
            for (int i = 0; i < transProto.count; i++) {
                transformSubProto sub;
                auto& subVal = it["data"].GetArray()[i];
                sub.transformIndex = subVal["source"].GetInt();
                transProto.subProtos.push_back(sub);
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 13:
            transProto.count = 0;
            if(it.HasMember("data")&&it["data"].IsArray())
                transProto.count = it["data"].GetArray().Size();
            transformSize += 2 + transProto.count* 10;
            for (int i = 0; i < transProto.count; i++) {
                transformSubProto sub;
                auto& subVal = it["data"].GetArray()[i];
                sub.transformIndex = subVal["transformIndex"].GetInt();
                sub.Val_0 = getJsonFloatValue(subVal,"val_0",0,constValueProtos);
                sub.Val_1 = getJsonFloatValue(subVal,"val_1",0,constValueProtos);
                sub.Val_2 = getJsonFloatValue(subVal,"val_2",0,constValueProtos);
                sub.Val_3 = getJsonFloatValue(subVal,"val_3",0,constValueProtos);
                transProto.subProtos.push_back(sub);
            }
            break;
        case 7:
        case 8:
        case 9:
            transProto.count = 0;
            if(it.HasMember("data")&&it["data"].IsArray())
                transProto.count = it["data"].GetArray().Size();
            transformSize += 2 + transProto.count* 20;
            for (int i = 0; i < transProto.count; i++) {
                transformSubProto sub;
                auto& subVal = it["data"].GetArray()[i];
                sub.transformIndex = subVal["transformIndex"].GetInt();
                sub.someIndex = subVal["someIndex"].GetInt();
                sub.Val_0 = getJsonFloatValue(subVal,"val_0",0,constValueProtos);
                sub.Val_1 = getJsonFloatValue(subVal,"val_1",0,constValueProtos);
                sub.Val_2 = getJsonFloatValue(subVal,"val_2",0,constValueProtos);
                sub.Val_3 = getJsonFloatValue(subVal,"val_3",0,constValueProtos);
                sub.Val_4 = getJsonFloatValue(subVal,"val_4",0,constValueProtos);
                sub.Val_5 = getJsonFloatValue(subVal,"val_5",0,constValueProtos);
                sub.Val_6 = getJsonFloatValue(subVal,"val_6",0,constValueProtos);
                sub.Val_7 = getJsonFloatValue(subVal,"val_7",0,constValueProtos);
                transProto.subProtos.push_back(sub);
            }
            break;
        case 10:
            transProto.count = 0;
            if(it.HasMember("data")&&it["data"].IsArray())
                transProto.count = it["data"].GetArray().Size();
            transformSize += 2 + transProto.count* 15;
            for (int i = 0; i < transProto.count; i++) {
                transformSubProto sub;
                auto& subVal = it["data"].GetArray()[i];
                sub.transformIndex = subVal["transformIndex"].GetInt();
                sub.someIndex = subVal["someIndex"].GetInt();
                sub.Val_0 = getJsonFloatValue(subVal,"val_0",0,constValueProtos);
                sub.Val_1 = getJsonFloatValue(subVal,"val_1",0,constValueProtos);
                sub.Val_2 = getJsonFloatValue(subVal,"val_2",0,constValueProtos);
                sub.Val_3 = getJsonFloatValue(subVal,"val_3",0,constValueProtos);
                sub.Val_4 = getJsonFloatValue(subVal,"val_4",0,constValueProtos);
                sub.Val_5 = getJsonFloatValue(subVal,"val_5",0,constValueProtos);
                sub.Val_6 = getJsonFloatValue(subVal,"val_6",0,constValueProtos);
                sub.Val_7 = getJsonFloatValue(subVal,"val_7",0,constValueProtos);
                sub.Val_8 = getJsonFloatValue(subVal,"val_8",0,constValueProtos);
                sub.Val_9 = getJsonFloatValue(subVal,"val_9",0,constValueProtos);
                sub.Val_10 = getJsonFloatValue(subVal,"val_10",0,constValueProtos);
                sub.Val_11 = getJsonFloatValue(subVal,"val_11",0,constValueProtos);
                sub.Val_12 = getJsonFloatValue(subVal,"val_12",0,constValueProtos);
                transProto.subProtos.push_back(sub);
            }
            break;
        case 11:
            transProto.count = 0;
            if(it.HasMember("data")&&it["data"].IsArray())
                transProto.count = it["data"].GetArray().Size();
            transformSize += 2 + transProto.count* 8;
            for (int i = 0; i < transProto.count; i++) {
                transformSubProto sub;
                auto& subVal = it["data"].GetArray()[i];
                sub.transformIndex = subVal["transformIndex"].GetInt();
                sub.Val_0 = getJsonFloatValue(subVal,"rotation",0,constValueProtos);
                sub.Val_1 = getJsonFloatValue(subVal,"centerX",0.5,constValueProtos);
                sub.Val_2 = getJsonFloatValue(subVal,"centerY",0.5,constValueProtos);
                transProto.subProtos.push_back(sub);
            }
            break;
        case 12:
            transProto.count = 0;
            if(it.HasMember("data")&&it["data"].IsArray())
                transProto.count = it["data"].GetArray().Size();
            transformSize += 2 + transProto.count* 6;
            for (int i = 0; i < transProto.count; i++) {
                transformSubProto sub;
                auto& subVal = it["data"].GetArray()[i];
                sub.transformIndex = subVal["transformIndex"].GetInt();
                sub.someIndex = subVal["val_0"].GetInt();
                sub.iVal_1 = subVal["val_1"].GetInt();
                transProto.subProtos.push_back(sub);
            }
            break;
        default:
            Error("Rui unknown transformation type");
            continue;
        }
        transformPrototypes.push_back(transProto);
    }

    for (auto& val : constValueProtos) {
        switch (val.type) {
        case TYPE_INT:
        case TYPE_FLOAT:
        case TYPE_BOOL:
            constsSize += 4;
            break;
        case TYPE_STRING:
        case TYPE_UIHANDLE:
        case TYPE_ASSET:
            constsSize += 8;
            break;
        }
    }

    for (auto& it : mapEntry["args"].GetArray())
    {
        RuiArgumentProto proto;
        proto.valueOffset = 0;
        std::string typeStr = it["type"].GetStdString();
        proto.type = ruiArgTypeFromStr[typeStr];
        proto.name = it["name"].GetStdString();
        proto.nameOffset = nameStringsSize;
        nameStringsSize += proto.name.size() +1;
        switch (proto.type) {
        case TYPE_BOOL:
        case TYPE_INT:
            proto.value.asInt = it["value"].GetInt();
            proto.valueOffset = constsSize +argsSize;
            argsSize +=4;
            break;
        case TYPE_STRING:
        case TYPE_ASSET:
        case TYPE_IMAGE:
            proto.stringValue = it["value"].GetString();
            constStringsSize += proto.stringValue.size() +1;
            proto.valueOffset = constsSize +argsSize;
            argsSize +=8;
            break;
        case TYPE_FLOAT:
        case TYPE_GAMETIME:
        case TYPE_WALLTIME:
            proto.value.asFloat = it["value"].GetFloat();
            proto.valueOffset = constsSize +argsSize;
            argsSize +=4;
            break;
        case TYPE_FLOAT2:
            proto.value.asVec2D[0] = it["value"].GetArray()[0].GetFloat();
            proto.value.asVec2D[1] = it["value"].GetArray()[1].GetFloat();
            proto.valueOffset = constsSize +argsSize;
            argsSize +=8;
            break;
        case TYPE_FLOAT3:
            proto.value.asVec3D[0] = it["value"].GetArray()[0].GetFloat();
            proto.value.asVec3D[1] = it["value"].GetArray()[1].GetFloat();
            proto.value.asVec3D[2] = it["value"].GetArray()[2].GetFloat();
            proto.valueOffset = constsSize +argsSize;
            argsSize +=12;
            break;
        case TYPE_COLOR_ALPHA:
            proto.value.asVec4D[0] = it["value"].GetArray()[0].GetFloat();
            proto.value.asVec4D[1] = it["value"].GetArray()[1].GetFloat();
            proto.value.asVec4D[2] = it["value"].GetArray()[2].GetFloat();
            proto.value.asVec4D[3] = it["value"].GetArray()[3].GetFloat();
            proto.valueOffset = constsSize +argsSize;
            argsSize +=16;
            break;
        default:
            Error("arg type not supported");
        }
        argumentPrototypes.push_back(proto);
    }

    int argCount;
    if (argumentPrototypes.size()) {
        argCount = 1;
        while (argCount < argumentPrototypes.size()) {
            argCount *=2;
        }
    }
    else {
        argCount = 0;
    }
    //set runtime value offsets
    for (auto& trans : transformPrototypes) {
        switch (trans.type) {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 13:
            for (int i = 0; i < trans.count; i++) {

                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_0);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_1);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_2);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_3);
            }
            break;
        case 7:
        case 8:
        case 9:
            for (int i = 0; i < trans.count; i++) {

                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_0);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_1);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_2);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_3);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_4);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_5);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_6);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_7);
            }
            break;
        case 10:
            for (int i = 0; i < trans.count; i++) {

                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_0);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_1);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_2);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_3);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_4);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_5);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_6);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_7);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_8);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_9);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_10);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_11);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_12);
            }
            break;
        case 11:
            for (int i = 0; i < trans.count; i++) {

                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_0);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_1);
                setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,trans.subProtos[i].Val_2);
            }
            break;
        }

    }
    for (auto& unk : unknown8Prototypes) {

        switch(unk.type){
        case 0:  //is font
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1C);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_20);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_22);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_24);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_26);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_28);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_2A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_2C);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_2E);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_30);

            break;
        case 1:
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1C);
            break;
        case 2: 
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color0_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color1_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_red);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_green);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_blue);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.color2_alpha);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1C);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1E);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_20);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_22);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_24);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_26);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_28);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_2A);
        }

    }
    for (auto& unk : unknown9Prototypes) {
        switch (unk.type) {
        case 0:
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_8);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_C);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_E);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_10);
            break;
        case 1:
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_4);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_6);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_8);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_C);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_E);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_10);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_12);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_14);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_16);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_18);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1C);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_1E);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_20);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_22);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_24);

            break;
        case 2:
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_4);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_6);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_8);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_A);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_C);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_E);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_10);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_12);
            setDynamicOffset(argumentPrototypes,dynamicValuePrototypes,dynamicValuesSize,constsSize + argsSize,unk.Val_14);
            break;
        } 
    }


    unknown8dataStruct* unknown8Buf = (unknown8dataStruct*)malloc(sizeof(unknown8dataStruct)* unknown8Prototypes.size());
    memset(unknown8Buf,0,sizeof(unknown8dataStruct)* unknown8Prototypes.size());
    int i = 0;

    
    for (auto& proto : unknown8Prototypes) {
        unknown8Buf[i].type = proto.type;
        unknown8Buf[i].word_2 = proto.color0_red.offset;
        unknown8Buf[i].word_4 = proto.color0_green.offset;
        unknown8Buf[i].word_6 = proto.color0_blue.offset;
        unknown8Buf[i].word_8 = proto.color0_alpha.offset;
        unknown8Buf[i].word_A = proto.color1_red.offset;
        unknown8Buf[i].word_C = proto.color1_green.offset;
        unknown8Buf[i].word_E = proto.color1_blue.offset;
        unknown8Buf[i].word_10 = proto.color1_alpha.offset;
        unknown8Buf[i].word_12 = proto.color2_red.offset;
        unknown8Buf[i].word_14 = proto.color2_green.offset;
        unknown8Buf[i].word_16 = proto.color2_blue.offset;
        unknown8Buf[i].word_18 = proto.color2_alpha.offset;
        unknown8Buf[i].word_1A = proto.Val_1A.offset;
        unknown8Buf[i].word_1C = proto.Val_1C.offset;
        unknown8Buf[i].word_1E = proto.Val_1E.offset;
        unknown8Buf[i].word_20 = proto.Val_20.offset;
        unknown8Buf[i].word_22 = proto.Val_22.offset;
        unknown8Buf[i].word_24 = proto.Val_24.offset;
        unknown8Buf[i].word_26 = proto.Val_26.offset;
        unknown8Buf[i].word_28 = proto.Val_28.offset;
        unknown8Buf[i].word_2A = proto.Val_2A.offset;
        unknown8Buf[i].word_2C = proto.Val_2C.offset;
        unknown8Buf[i].word_2E = proto.Val_2E.offset;
        unknown8Buf[i].word_30 = proto.Val_30.offset;
        if(proto.type == 0)//is font
            unknown8Buf[i].word_1E = proto.fontIndex;
        i++;

    }
    char* unknown9Buf = new char[unknown9Size];
    //memset(unknown9Buf,0,unknown9Size);
    size_t unknown9Offset = 0;
    for (auto& proto : unknown9Prototypes) {
        switch (proto.type) {
        case 0: {
            unknown9dataStruct_0* unk9 = (unknown9dataStruct_0*) &unknown9Buf[unknown9Offset];
            Log("Unk9 Text Offset %lld\n",unknown9Offset);
            unknown9Offset += 0x12;
            unk9->type = proto.type;
            unk9->transformIndex = proto.transform_Index;
            unk9->uint8_4 = proto.unk8Index_0;
            unk9->uint8_5 = proto.unk8Index_1;
            unk9->uint8_6 = proto.unk8Index_2;
            unk9->uint8_7 = proto.unk8Index_3;
            unk9->textOffset = proto.Val_8.offset;
            unk9->uint16_A = proto.Val_A.offset;
            unk9->uint16_C = proto.Val_C.offset;
            unk9->uint16_E = proto.Val_E.offset;
            unk9->uint16_10 = proto.Val_10.offset;
            break;
        } 
        case 1: {
            unknown9dataStruct_1* unk9 = (unknown9dataStruct_1*) &unknown9Buf[unknown9Offset];
            
            unknown9Offset += 0x2A;
            unk9->type = proto.type;
            unk9->transformIndex = proto.transform_Index;
            unk9->uint16_4 = proto.Val_4.offset;
            unk9->uint16_6 = proto.Val_6.offset;
            unk9->uint16_8 = proto.Val_8.offset;
            unk9->uint16_A = proto.Val_A.offset;
            unk9->uint16_C = proto.Val_C.offset;
            unk9->uint16_E = proto.Val_E.offset;
            unk9->uint16_10 = proto.Val_10.offset;
            unk9->uint16_12 = proto.Val_12.offset;
            unk9->uint16_14 = proto.Val_14.offset;
            unk9->uint16_16 = proto.Val_16.offset;
            unk9->uint16_18 = proto.Val_18.offset;
            unk9->uint16_1A = proto.Val_1A.offset;
            unk9->uint16_1C = proto.Val_1C.offset;
            unk9->uint16_1E = proto.Val_1E.offset;
            unk9->uint16_20 = proto.Val_20.offset;
            unk9->uint16_22 = proto.Val_22.offset;
            unk9->uint16_24 = proto.Val_24.offset;
            unk9->word_26 = proto.word;
            unk9->uint8_28 = proto.unk8Index_0;
            break;
        }
        case 2: {
            unknown9dataStruct_2* unk9 = (unknown9dataStruct_2*) &unknown9Buf[unknown9Offset];
            unknown9Offset += 0x1A;
            unk9->type = proto.type;
            unk9->transformIndex = proto.transform_Index;
            unk9->uint16_4 = proto.Val_4.offset;
            unk9->uint16_6 = proto.Val_6.offset;
            unk9->uint16_8 = proto.Val_8.offset;
            unk9->uint16_A = proto.Val_A.offset;
            unk9->uint16_C = proto.Val_C.offset;
            unk9->uint16_E = proto.Val_E.offset;
            unk9->uint16_10 = proto.Val_10.offset;
            unk9->uint16_12 = proto.Val_12.offset;
            unk9->uint16_14 = proto.Val_14.offset;
            unk9->word_16 = proto.word;
            unk9->uint8_18 = proto.unk8Index_0;
            break;
        }
        }
    }
    char* transformBuf = new char[transformSize + 1];
    memset(transformBuf,0,transformSize +1);
    rmem tBuf(transformBuf);

    for (auto& trans : transformPrototypes) {
        tBuf.write<uint8_t>(trans.type);
        switch (trans.type) {
        case 1:
            tBuf.write<uint8_t>(trans.count);
            for (auto& subTrans : trans.subProtos) {
                tBuf.write<uint16_t>(subTrans.transformIndex);
            }
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 13:
            tBuf.write<uint8_t>(trans.count);
            for (auto& subTrans : trans.subProtos) {
                tBuf.write<uint16_t>(subTrans.transformIndex);
                tBuf.write<uint16_t>(subTrans.Val_0.offset);
                tBuf.write<uint16_t>(subTrans.Val_1.offset);
                tBuf.write<uint16_t>(subTrans.Val_2.offset);
                tBuf.write<uint16_t>(subTrans.Val_3.offset);
            }
            break;
        case 7:
        case 8:
        case 9:
            tBuf.write<uint8_t>(trans.count);
            for (auto& subTrans : trans.subProtos) {
                tBuf.write<uint16_t>(subTrans.transformIndex);
                tBuf.write<uint16_t>(subTrans.Val_0.offset);
                tBuf.write<uint16_t>(subTrans.Val_1.offset);
                tBuf.write<uint16_t>(subTrans.someIndex);
                tBuf.write<uint16_t>(subTrans.Val_2.offset);
                tBuf.write<uint16_t>(subTrans.Val_3.offset);
                tBuf.write<uint16_t>(subTrans.Val_4.offset);
                tBuf.write<uint16_t>(subTrans.Val_5.offset);
                tBuf.write<uint16_t>(subTrans.Val_6.offset);
                tBuf.write<uint16_t>(subTrans.Val_7.offset);
            }
            break;
        case 10:

            tBuf.write<uint8_t>(trans.count);
            for (auto& subTrans : trans.subProtos) {
                tBuf.write<uint16_t>(subTrans.transformIndex);
                tBuf.write<uint16_t>(subTrans.Val_0.offset);
                tBuf.write<uint16_t>(subTrans.Val_1.offset);
                tBuf.write<uint16_t>(subTrans.someIndex);
                tBuf.write<uint16_t>(subTrans.Val_2.offset);
                tBuf.write<uint16_t>(subTrans.Val_3.offset);
                tBuf.write<uint16_t>(subTrans.Val_4.offset);
                tBuf.write<uint16_t>(subTrans.Val_5.offset);
                tBuf.write<uint16_t>(subTrans.Val_6.offset);
                tBuf.write<uint16_t>(subTrans.Val_7.offset);
                tBuf.write<uint16_t>(subTrans.Val_8.offset);
                tBuf.write<uint16_t>(subTrans.Val_9.offset);
                tBuf.write<uint16_t>(subTrans.Val_10.offset);
                tBuf.write<uint16_t>(subTrans.Val_11.offset);
                tBuf.write<uint16_t>(subTrans.Val_12.offset);
            }
            break;

        case 11:
            tBuf.write<uint8_t>(trans.count);
            for (auto& subTrans : trans.subProtos) {
                tBuf.write<uint16_t>(subTrans.transformIndex);
                tBuf.write<uint16_t>(subTrans.Val_0.offset);
                tBuf.write<uint16_t>(subTrans.Val_1.offset);
                tBuf.write<uint16_t>(subTrans.Val_2.offset);
            }
            break;
        case 12:
            tBuf.write<uint8_t>(trans.count);
            for (auto& subTrans : trans.subProtos) {
                tBuf.write<uint16_t>(subTrans.transformIndex);
                tBuf.write<uint16_t>(subTrans.someIndex);
                tBuf.write<uint16_t>(subTrans.iVal_1);
            }
            break;
        }
    }
    tBuf.write<uint8_t>(0);
    
    // WRITE THE CONSTS AND ARGS
    char* nameStringsBuf = new char[nameStringsSize];
    memset(nameStringsBuf,0,nameStringsSize);

    // create buffer for values
    char* valuesBuf = new char[constsSize + argsSize]{};
    rmem vBuf(valuesBuf);

    // create buffer for default strings
    char* constStringsBuf = new char[constStringsSize + 1]{};
    uint32_t curStringOffset = 0;

    // create the seginfo for the values


    // create the seginfo for the default strings
    _vseginfo_t constStringsInfo{};
    if(constStringsSize)
        constStringsInfo = pak->CreateNewSegment(constStringsSize +1, SF_CLIENT | SF_CPU, 1);

    
    _vseginfo_t nameStringsInfo{};
    nameStringsInfo = pak->CreateNewSegment(nameStringsSize,SF_CLIENT |SF_CPU |SF_DEV,1);

    _vseginfo_t valuesInfo{};
    valuesInfo = pak->CreateNewSegment(constsSize + argsSize, SF_CLIENT | SF_CPU, 1);
    
    _vseginfo_t transformInfo{};
    transformInfo = pak->CreateNewSegment(transformSize +1,SF_CLIENT|SF_CPU,1);

    _vseginfo_t unk8Info{};
    unk8Info = pak->CreateNewSegment(sizeof(unknown8dataStruct) * unknown8Prototypes.size(), SF_CLIENT | SF_CPU, 1);

    _vseginfo_t unk9Info{};
    unk9Info = pak->CreateNewSegment(unknown9Size,SF_CLIENT | SF_CPU ,1);

    // create the seginfo for the args
    _vseginfo_t argsInfo{};
    // for now, just contains a single arg cluster and all of the args
    argsInfo = pak->CreateNewSegment(sizeof(RuiArgCluster) + sizeof(RuiArg) * argCount, SF_CLIENT | SF_CPU, 1);




    char* argsBuf = new char[sizeof(RuiArgCluster) + sizeof(RuiArg) * argCount]{};
    memset(argsBuf,0,sizeof(RuiArgCluster)+ sizeof(RuiArg)*argCount);
    
    // write the arg cluster
    RuiArgCluster cluster;

    cluster.argCount = argCount;
    cluster.argIndex = 0;



    calculateHashVars(cluster,argumentPrototypes);

    
    
    // write the args
    RuiArg* args = (RuiArg*)&argsBuf[sizeof(RuiArgCluster)];
    for (auto& argProto : argumentPrototypes) {
        memcpy(&nameStringsBuf[argProto.nameOffset],argProto.name.c_str(),argProto.name.size());
        uint32_t shortHash = calculateShortHash(argProto.name.c_str(),cluster.byte1,cluster.byte2);
        uint32_t index = shortHash & (argCount-1);
        args[index].type = argProto.type;
        args[index].unk1 = 0;
        args[index].valueOffset = argProto.valueOffset;
        args[index].nameOffset = argProto.nameOffset;
        args[index].short_hash = shortHash >> 4;
    }
    
    for (auto& val : constValueProtos) {
        vBuf.seek(val.valueOffset,rseekdir::beg);
        switch (val.type) {
        case TYPE_FLOAT:
        case TYPE_INT:
        case TYPE_BOOL:
            vBuf.write<int>(val.value.asInt);
            break;
        case TYPE_STRING:
        case TYPE_ASSET:
        case TYPE_UIHANDLE:
            memcpy(&constStringsBuf[curStringOffset],val.stringValue.c_str(),val.stringValue.size());
            vBuf.write<uint32_t>(valuesInfo.index,curStringOffset);
            pak->AddPointer(valuesInfo.index,val.valueOffset);
            curStringOffset += val.stringValue.size() + 1;
            break;
        default:
            Error("Unsupported Type in Values");
        }
    }
    for (auto& val : argumentPrototypes) {
        vBuf.seek(val.valueOffset,rseekdir::beg);
        switch (val.type) {
        case TYPE_FLOAT:
        case TYPE_INT:
        case TYPE_BOOL:
            vBuf.write<int>(val.value.asInt);
            break;
        case TYPE_STRING:
        case TYPE_ASSET:
        case TYPE_UIHANDLE:
            memcpy(&constStringsBuf[curStringOffset],val.stringValue.c_str(),val.stringValue.size());
            vBuf.write<uint32_t>(constStringsInfo.index,curStringOffset);
            pak->AddPointer(valuesInfo.index,val.valueOffset);
            curStringOffset += val.stringValue.size() + 1;
            break;
        case TYPE_FLOAT2:
            vBuf.write<float>(val.value.asVec2D[0]);
            vBuf.write<float>(val.value.asVec2D[1]);
            break;
        case TYPE_FLOAT3:
            vBuf.write<float>(val.value.asVec3D[0]);
            vBuf.write<float>(val.value.asVec3D[1]);
            vBuf.write<float>(val.value.asVec3D[2]);
            break;
        case TYPE_COLOR_ALPHA:
            vBuf.write<float>(val.value.asVec4D[0]);
            vBuf.write<float>(val.value.asVec4D[1]);
            vBuf.write<float>(val.value.asVec4D[2]);
            vBuf.write<float>(val.value.asVec4D[3]);
            break;
        default:
            Error("Unsupported Type in Values");
        }
    }


    cluster.unk_6 = 0;
    cluster.dataStructSize = constsSize + argsSize + dynamicValuesSize;
    cluster.valueSize = constsSize + argsSize;
    cluster.short_C = 1;
    cluster.short_E = 0;
    cluster.unk9Count = unknown9Prototypes.size();

    *(RuiArgCluster*)argsBuf = cluster;
    //////////////////////
    // ASSET SUBHEADER
    

    // set the width and height
    pHdr->elementWidth = mapEntry["width"].GetFloat();
    pHdr->elementWidthRatio = 1 / pHdr->elementWidth;
    pHdr->elementHeight = mapEntry["height"].GetFloat();
    pHdr->elementHeightRatio = 1 / pHdr->elementHeight;

    // set args size and total struct size
    pHdr->valueSize = constsSize + argsSize;
    pHdr->structSize = pHdr->valueSize + varsSize;

    // register the pointer to the name
    pak->AddPointer(subhdrinfo.index, offsetof(RuiHeader, name));
    // set the pointer to the asset name
    pHdr->name = { assetNameInfo.index, 0 };

    // register the pointer to the values
    pak->AddPointer(subhdrinfo.index, offsetof(RuiHeader, values));
    // set the pointer to the asset values
    pHdr->values = { valuesInfo.index, 0 };

    pak->AddPointer(subhdrinfo.index, offsetof(RuiHeader, transformData));
    pHdr->transformData = { transformInfo.index,0};

    pak->AddPointer(subhdrinfo.index, offsetof(RuiHeader, unk8));
    pHdr->unk8 = { unk8Info.index,0};

    pak->AddPointer(subhdrinfo.index, offsetof(RuiHeader, unk9));
    pHdr->unk9 = { unk9Info.index,0};
    
    pak->AddPointer(subhdrinfo.index,offsetof(RuiHeader, argClusters));
    pHdr->argClusters = {argsInfo.index,0};

    pak->AddPointer(subhdrinfo.index,offsetof(RuiHeader, args));
    pHdr->args = {argsInfo.index,sizeof(RuiArgCluster)};

    pak->AddPointer(subhdrinfo.index, offsetof(RuiHeader,argNames));
    pHdr->argNames = {nameStringsInfo.index,0};

    pHdr->argCount = argCount;
    pHdr->unk10Count = 0;//TODO unk 10
    pHdr->structSize = constsSize + argsSize + dynamicValuesSize;
    pHdr->valueSize = constsSize + argsSize;
    pHdr->unk8Count = unknown8Prototypes.size();
    pHdr->unk6 = 0;
    if (mapEntry.HasMember("unk6") && mapEntry["unk6"].IsInt()) {
        pHdr->unk6 = mapEntry["unk6"].GetInt();
    }
    pHdr->unk9Count = unknown9Prototypes.size();
    pHdr->argClusterCount = 1;

    ////////////////////
    // FINISHING UP
    // add the raw data blocks in order


    // subheader
    RPakRawDataBlock shdb{ subhdrinfo.index, subhdrinfo.size, (uint8_t*)pHdr };
    pak->AddRawDataBlock(shdb);

    // asset name
    RPakRawDataBlock andb{ assetNameInfo.index, assetNameInfo.size, (uint8_t*)namebuf };
    pak->AddRawDataBlock(andb);



    if (constStringsSize) {
        // default string values
        RPakRawDataBlock sdb{ constStringsInfo.index, constStringsInfo.size, (uint8_t*)constStringsBuf };
        pak->AddRawDataBlock(sdb);
    }


    RPakRawDataBlock ndb { nameStringsInfo.index, nameStringsInfo.size,(uint8_t*)nameStringsBuf};
    pak->AddRawDataBlock(ndb);

    // values
    RPakRawDataBlock vdb{ valuesInfo.index, valuesInfo.size, (uint8_t*)valuesBuf };
    pak->AddRawDataBlock(vdb);

    RPakRawDataBlock tdb{transformInfo.index,transformInfo.size,(uint8_t*)transformBuf};
    pak->AddRawDataBlock(tdb);

    RPakRawDataBlock u8db{unk8Info.index,unk8Info.size,(uint8_t*)unknown8Buf};
    pak->AddRawDataBlock(u8db);

    RPakRawDataBlock u9db{unk9Info.index,unk9Info.size,(uint8_t*)unknown9Buf};
    pak->AddRawDataBlock(u9db);

    RPakRawDataBlock adb{ argsInfo.index,argsInfo.size,(uint8_t*)argsBuf};
    pak->AddRawDataBlock(adb);




    //arg names

    // create and init the asset entry
    RPakAssetEntry asset;
    asset.InitAsset(RTech::StringToGuid((std::string("ui/") + name + ".rpak").c_str()), subhdrinfo.index, 0, subhdrinfo.size, -1, 0, -1, -1, (std::uint32_t)AssetType::UI);
    asset.version = 0x1E;
    
    asset.pageEnd = argsInfo.index + 1; // number of the highest page that the asset references pageidx + 1
    asset.unk1 = 1;
    // add the asset entry
    assetEntries->push_back(asset);
    std::map<RuiArgumentType_t, const char*> argTypeName{
        {TYPE_STRING,"const char*"},
        {TYPE_ASSET,"const char*"},
        {TYPE_BOOL,"int"},
        {TYPE_INT,"int"},
        {TYPE_FLOAT,"float"},
        {TYPE_FLOAT2,"float"},
        {TYPE_FLOAT3,"float"},
        {TYPE_COLOR_ALPHA,"float"},
        {TYPE_GAMETIME,"float"},
        {TYPE_WALLTIME,"float"},
        {TYPE_UIHANDLE,"const char*"},
    };
    size_t cppStructOffset = 0;
    std::string cppStruct = std::string("__unaligned struct data_") + name + "{\n";
    char constGapBuffer[1024];
    sprintf_s(constGapBuffer,"\tBYTE gap_0[%lld];\n",constsSize);
    cppStruct += constGapBuffer;
    cppStructOffset = constsSize;
    for (auto& proto : argumentPrototypes) {
        char argumentStringBuffer[1024];
        if (proto.valueOffset > cppStructOffset) {
            //ADD gap;
            char constGapBuffer[1024];
            sprintf_s(constGapBuffer,"\tBYTE gap_%llx[%lld];\n",cppStructOffset,proto.valueOffset-cppStructOffset);
            cppStruct += constGapBuffer;
            cppStructOffset = proto.valueOffset;
        }
        cppStructOffset += ruiArgSizeFromType[proto.type];
        switch (proto.type) {
        case TYPE_FLOAT2:
            sprintf_s(argumentStringBuffer, "\tfloat %s[2];\n", proto.name.c_str());
            break;
        case TYPE_FLOAT3:
            sprintf_s(argumentStringBuffer, "\tfloat %s[3];\n", proto.name.c_str());
            break;
        case TYPE_COLOR_ALPHA:
            sprintf_s(argumentStringBuffer, "\tfloat %s[4];\n", proto.name.c_str());
            break;
        default:
            sprintf_s(argumentStringBuffer, "\t%s %s;\n", argTypeName[proto.type], proto.name.c_str());
            break;
        }
        
        cppStruct+= argumentStringBuffer;
    }
    for (auto& proto : dynamicValuePrototypes) {
        char argumentStringBuffer[1024];
        if (proto.offset > cppStructOffset) {
            //ADD gap;
            char constGapBuffer[1024];
            sprintf_s(constGapBuffer,"\tBYTE gap_%llX[%lld];\n",cppStructOffset,proto.offset-cppStructOffset);
            cppStructOffset = proto.offset;
            cppStruct += constGapBuffer;
        }
        cppStructOffset += ruiArgSizeFromType[proto.type];
        switch (proto.type) {
        case TYPE_FLOAT2:
            sprintf_s(argumentStringBuffer, "\tfloat %s[2];\n", proto.name.c_str());
            break;
        case TYPE_FLOAT3:
            sprintf_s(argumentStringBuffer, "\tfloat %s[3];\n", proto.name.c_str());
            break;
        case TYPE_COLOR_ALPHA:
            sprintf_s(argumentStringBuffer, "\tfloat %s[4];\n", proto.name.c_str());
            break;
        default:
            sprintf_s(argumentStringBuffer, "\t%s %s;\n", argTypeName[proto.type], proto.name.c_str());
        }
        cppStruct+= argumentStringBuffer;
    }
    Log("%s\n};\n",cppStruct.c_str());

    Log("transform Size: %lld\n",transformSize);
    

}
