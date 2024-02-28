/*
 * @
 * @ Copyright Simple Game Studios/Basic/Lewis Herbert, All Rights Reserved. @2022
 * @
 *
 *  If ya'll need help with anything to do with this product hit me up:
 *  Twitter: @CusYaBasic
 *  Discord: CusYaBasic#9194
 *  Email: cusyabasic@hotmail.com
 *
 *  Last but not least, Ya Basic!
 *
 */

#include "BasicLevelSystem.h"

#define LOCTEXT_NAMESPACE "FBasicLevelSystemModule"

void FBasicLevelSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FBasicLevelSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBasicLevelSystemModule, BasicLevelSystem)