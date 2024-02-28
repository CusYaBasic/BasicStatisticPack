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

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBasicCurrencySystemModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
