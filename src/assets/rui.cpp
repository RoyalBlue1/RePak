#include "pch.h"
#include "assets/assets.h"
#include "public/rui.h"



struct RuiPackageHeader {
	uint32_t magic;
	uint32_t packageVersion;
	uint32_t ruiVersion;
	uint32_t ruiHeaderOffset;
	uint32_t dataBlockHeaderOffset;
	uint32_t argNamesOffset;
	uint32_t argNamesSize;
};


struct RuiPackageDataBlockHeader {
	uint32_t dataBlockOffset;
	uint32_t dataBlockSize;
	uint32_t dataStructInitData;
	uint32_t transformData;
	uint32_t argClusters;
	uint32_t args;
	uint32_t styleDescriptors;
	uint32_t renderJobData;
};


void Assets::AddRuiAsset_v30(CPakFile* pak, const char* assetPath, rapidjson::Value& /*mapEntry*/) {
	Log("Adding rui asset '%s'\n",assetPath);

	const fs::path inputFilePath = pak->GetAssetPath() / fs::path(assetPath).replace_extension("ruip");

	if (!fs::exists(inputFilePath))
		Error("Failed to find compiled shader file for asset '%s' (%s).\n", assetPath, inputFilePath.string().c_str());

	FILE* f = NULL;
	if (fopen_s(&f, inputFilePath.string().c_str(), "rb") != 0) {
		Error("Error during read of file '%s'", inputFilePath.string().c_str());
		return;
	}
	RuiPackageHeader fileHeader;
	fread(&fileHeader,sizeof(RuiPackageHeader),1,f);
	if (fileHeader.magic!=0x50495552) 
		Error("File is not an ruip file for asset '%s' (%s)",assetPath,inputFilePath.string().c_str());
	if (fileHeader.packageVersion!= 1) 
		Error("File version mismatch is %d should be 1 with file '%s' (%s)",fileHeader.packageVersion,assetPath,inputFilePath.string().c_str());
	if (fileHeader.ruiVersion!= 30) 
		Error("Rui version mismatch is %d should be 30 with file '%s' (%s)",fileHeader.ruiVersion,assetPath,inputFilePath.string().c_str());



	//TODO check rui version and file version as well
	CPakDataChunk hdrChunk = pak->CreateDataChunk(sizeof(RuiAssetHeader_v30_t),SF_HEAD | SF_CLIENT,8);
	const fs::path pakFilePath = fs::path(assetPath).replace_extension("");



	const std::string assetPathWithoutExtension = fs::path(assetPath).replace_extension("").string();

	CPakDataChunk nameChunk = pak->CreateDataChunk(assetPathWithoutExtension.length() + 1, SF_CPU | SF_CLIENT, 1);
	strcpy_s(nameChunk.Data(), nameChunk.GetSize(), assetPathWithoutExtension.c_str());

	RuiAssetHeader_v30_t* const hdr = reinterpret_cast<RuiAssetHeader_v30_t*>(hdrChunk.Data());
	fseek(f,fileHeader.ruiHeaderOffset,0);
	fread(hdr,sizeof(RuiAssetHeader_v30_t),1,f);

	RuiPackageDataBlockHeader dataBlockHeader;
	fseek(f,fileHeader.dataBlockHeaderOffset,0);
	fread(&dataBlockHeader,sizeof(RuiPackageDataBlockHeader),1,f);
	
	CPakDataChunk dataChunk = pak->CreateDataChunk(dataBlockHeader.dataBlockSize,SF_CPU|SF_CLIENT,8);
	fseek(f,16,SEEK_SET);

	fseek(f,dataBlockHeader.dataBlockOffset,0);
	fread(dataChunk.Data(),dataBlockHeader.dataBlockSize,1,f);
	


	hdr->name = nameChunk.GetPointer();
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,name)));
	hdr->dataStructInitData = dataChunk.GetPointer(dataBlockHeader.dataStructInitData);
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,dataStructInitData)));
	hdr->transformData = dataChunk.GetPointer(dataBlockHeader.transformData);
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,transformData)));
	hdr->argClusters = dataChunk.GetPointer(dataBlockHeader.argClusters);
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,argClusters)));
	hdr->args = dataChunk.GetPointer(dataBlockHeader.args);
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,args)));
	hdr->styleDescriptors = dataChunk.GetPointer(dataBlockHeader.styleDescriptors);
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,styleDescriptors)));
	hdr->renderJobData = dataChunk.GetPointer(dataBlockHeader.renderJobData);
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,renderJobData)));

	CPakDataChunk argNamesChunk = pak->CreateDataChunk(fileHeader.argNamesSize,SF_CPU | SF_CLIENT | SF_DEV,1);
	fseek(f,fileHeader.argNamesOffset,0);
	fread(argNamesChunk.Data(), fileHeader.argNamesSize,1, f);

	hdr->argNames = argNamesChunk.GetPointer();
	pak->AddPointer(hdrChunk.GetPointer(offsetof(RuiAssetHeader_v30_t,argNames)));



	PakAsset_t asset;
	asset.InitAsset(std::string("ui/") + pakFilePath.string() + ".rpak",
		hdrChunk.GetPointer(), hdrChunk.GetSize(),
		PagePtr_t::NullPtr(), UINT64_MAX, UINT64_MAX, AssetType::UI);
	asset.SetHeaderPointer(hdrChunk.Data());
	asset.version = 30;
	asset.pageEnd = pak->GetNumPages();
	asset.remainingDependencyCount = 0;
	pak->PushAsset(asset);
	pak->SetPakFlag(1);
	
}