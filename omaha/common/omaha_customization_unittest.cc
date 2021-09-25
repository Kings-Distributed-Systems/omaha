// Copyright 2010 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ========================================================================
//
// Tests the constants that vary depending on the customization of Omaha.
// The test checks for the Google Update variations, but can be modified for
// your purposes.

#include <tchar.h>
#include "omaha/base/const_addresses.h"
#include "omaha/base/const_code_signing.h"
#include "omaha/base/const_config.h"
#include "omaha/base/const_debug.h"
#include "omaha/base/const_object_names.h"
#include "omaha/base/constants.h"
#include "omaha/base/logging.h"
#include "omaha/base/process.h"
#include "omaha/base/utils.h"
#include "omaha/common/config_manager.h"
#include "omaha/common/const_goopdate.h"
#include "omaha/common/const_group_policy.h"
#include "omaha/common/omaha_customization_proxy_clsid.h"
#include "omaha/testing/omaha_customization_test.h"

// TODO(omaha): Make use of EXPECT_GU_STREQ, etc.

namespace omaha {

TEST(OmahaCustomizationTest, Constants_BuildFiles) {
  // Primary main.scons values.

  // TODO(omaha): Most of these tests are of extremely questionable
  // value, as they're just checking that certain #defines exist and
  // haven't changed.  But, unanticipated changes to most of these
  // would cause build breaks anyways!  Consider deleting them.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ("Google LLC", FULL_COMPANY_NAME_ANSI);
  EXPECT_STREQ("Google", SHORT_COMPANY_NAME_ANSI);
  EXPECT_STREQ("Update", PRODUCT_NAME_ANSI);

  EXPECT_STREQ("google", COMPANY_DOMAIN_BASE_ANSI);
  EXPECT_STREQ("google.com", COMPANY_DOMAIN_ANSI);

  EXPECT_STREQ("Google Update", OMAHA_APP_NAME_ANSI);
#endif  // GOOGLE_UPDATE_BUILD

  EXPECT_STREQ("goopdate", MAIN_DLL_BASE_NAME_ANSI);

  const GUID kActualProxyClsidIsMachineGuid = PROXY_CLSID_IS_MACHINE;
  EXPECT_TRUE(::IsEqualGUID(kProxyClsidIsMachineGuid,
                            kActualProxyClsidIsMachineGuid));

  const GUID kActualProxyClsidIsUserGuid = PROXY_CLSID_IS_USER;
  EXPECT_TRUE(::IsEqualGUID(kProxyClsidIsUserGuid,
                            kActualProxyClsidIsUserGuid));

  // Primary omaha_version_utils values.
  EXPECT_STREQ(_T("np") SHORT_COMPANY_NAME _T("OneClick"), ONECLICK_PLUGIN_NAME);
  EXPECT_STREQ(_T("np") SHORT_COMPANY_NAME _T("Update"), UPDATE_PLUGIN_NAME);
}

TEST(OmahaCustomizationTest, Constants_Names) {
  // Company and product names.

  // TODO(omaha): Most of these tests are of extremely questionable
  // value, as they're just checking that certain #defines exist and
  // haven't changed.  But, unanticipated changes to most of these
  // would cause build breaks anyways!  Consider deleting them.
#ifdef GOOGLE_UPDATE_BUILD
  EXPECT_STREQ(_T("Google LLC"), kFullCompanyName);
  EXPECT_STREQ(_T("Google"), SHORT_COMPANY_NAME);
  EXPECT_STREQ(_T("Google"), kShortCompanyName);
  EXPECT_STREQ(_T("Update"), PRODUCT_NAME);

  EXPECT_STREQ(_T("google.com"), COMPANY_DOMAIN);

  // Full app name.
  EXPECT_STREQ(_T("Google Update"), kAppName);

  // Identifiers.
  EXPECT_STREQ(_T("Google"), COMPANY_NAME_IDENTIFIER);
  EXPECT_STREQ(_T("Update"), PRODUCT_NAME_IDENTIFIER);
  EXPECT_STREQ(_T("GoogleUpdate"), APP_NAME_IDENTIFIER);

  // Other values based on the app name.
  EXPECT_STREQ(_T("_Google_Update_"), kLockPrefix);

  // Filename bases
  EXPECT_STREQ(_T("GoogleUpdate"), MAIN_EXE_BASE_NAME);
#endif  // GOOGLE_UPDATE_BUILD
  EXPECT_STREQ(_T("goopdate"), MAIN_DLL_BASE_NAME);
}

TEST(OmahaCustomizationTest, Constants_Filenames) {
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T(".exe"), kOmahaShellFileName);
  EXPECT_STREQ(CRASH_HANDLER_NAME _T(".exe"), kCrashHandlerFileName);
  EXPECT_STREQ(CRASH_HANDLER_NAME _T("64.exe"), kCrashHandler64FileName);
  EXPECT_STREQ(_T("goopdate.dll"), kOmahaDllName);
  EXPECT_STREQ(_T("goopdateres_%s.dll"), kOmahaResourceDllNameFormat);
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T("Broker.exe"), kOmahaBrokerFileName);
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T("Core.exe"), kOmahaCoreFileName);
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T("OnDemand.exe"), kOmahaOnDemandFileName);
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T("Setup.exe"), kOmahaMetainstallerFileName);
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T("ComRegisterShell64.exe"),
               kOmahaCOMRegisterShell64);
  EXPECT_STREQ(_T("psmachine.dll"), kPSFileNameMachine);
  EXPECT_STREQ(_T("psmachine_64.dll"), kPSFileNameMachine64);
  EXPECT_STREQ(_T("psuser.dll"), kPSFileNameUser);
  EXPECT_STREQ(_T("psuser_64.dll"), kPSFileNameUser64);
}

TEST(OmahaCustomizationTest, Constants_Certificate) {
  EXPECT_STREQ(_T("Google LLC"), kSha1CertificateSubjectName);
  EXPECT_STREQ(_T("Google LLC"), kSha256CertificateSubjectName);
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_String) {
  EXPECT_STREQ(_T("{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), GOOPDATE_APP_ID);
  EXPECT_STREQ(_T("{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"),
               kGoogleUpdateAppId);
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_GUID) {
  const GUID kExpectedGoogleUpdateGuid =
      {0x2070893A, 0xB7CF, 0x42FD,
       {0x9B, 0xA1, 0xF0, 0x0E, 0x04, 0xA9, 0xD7, 0x66}};
  EXPECT_TRUE(::IsEqualGUID(kExpectedGoogleUpdateGuid, kGoopdateGuid));
  EXPECT_STREQ(_T("{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"),
               GuidToString(kGoopdateGuid));
}

TEST(OmahaCustomizationTest, Constants_OmahaAppId_GUIDAndStringMatch) {
  EXPECT_STREQ(kGoogleUpdateAppId, GuidToString(kGoopdateGuid));
}

TEST(OmahaCustomizationTest, Constants_Directories) {
  EXPECT_STREQ(_T("Offline"), OFFLINE_DIR_NAME);
  EXPECT_GU_STREQ(_T("Google"), OMAHA_REL_COMPANY_DIR);
  EXPECT_GU_STREQ(_T("Google\\CrashReports"), OMAHA_REL_CRASH_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update"), OMAHA_REL_GOOPDATE_INSTALL_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Log"), OMAHA_REL_LOG_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Offline"),
                  OMAHA_REL_OFFLINE_STORAGE_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Download"),
                  OMAHA_REL_DOWNLOAD_STORAGE_DIR);
  EXPECT_GU_STREQ(_T("Google\\Update\\Install"),
                  OMAHA_REL_INSTALL_WORKING_DIR);
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys_NotCustomized) {
  EXPECT_STREQ(_T("HKLM"), MACHINE_KEY_NAME);
  EXPECT_STREQ(_T("HKLM\\"), MACHINE_KEY);
  EXPECT_STREQ(_T("HKCU"), USER_KEY_NAME);
  EXPECT_STREQ(_T("HKCU\\"), USER_KEY);
  EXPECT_STREQ(_T("HKU\\"), USERS_KEY);
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys) {
  EXPECT_GU_STREQ(_T("Software\\Google\\"), COMPANY_MAIN_KEY);
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\"), GOOPDATE_MAIN_KEY);
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\Clients\\"), GOOPDATE_REG_RELATIVE_CLIENTS);  // NOLINT
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\ClientState\\"), GOOPDATE_REG_RELATIVE_CLIENT_STATE);  // NOLINT
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\ClientStateMedium\\"), GOOPDATE_REG_RELATIVE_CLIENT_STATE_MEDIUM);  // NOLINT
  EXPECT_GU_STREQ(_T("Software\\Policies\\Google\\"), COMPANY_POLICIES_MAIN_KEY);           // NOLINT
  EXPECT_GU_STREQ(_T("Software\\Policies\\Google\\Update\\"), GOOPDATE_POLICIES_RELATIVE);  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\"), USER_REG_GOOGLE);
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\"), USER_REG_UPDATE);
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\"), USER_REG_CLIENTS);  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), USER_REG_CLIENTS_GOOPDATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\"), USER_REG_CLIENT_STATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), USER_REG_CLIENT_STATE_GOOPDATE);  // NOLINT

  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\"), MACHINE_REG_GOOGLE);
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\"), MACHINE_REG_UPDATE);
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\"), MACHINE_REG_CLIENTS);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), MACHINE_REG_CLIENTS_GOOPDATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\"), MACHINE_REG_CLIENT_STATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), MACHINE_REG_CLIENT_STATE_GOOPDATE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientStateMedium\\"), MACHINE_REG_CLIENT_STATE_MEDIUM);  // NOLINT

  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\UpdateDev\\"), MACHINE_REG_UPDATE_DEV);  // NOLINT
}

TEST(OmahaCustomizationTest, Constants_RegistryKeys_GroupPolicy) {
  EXPECT_GU_STREQ(_T("Software\\Policies\\Google\\Update\\"), GOOPDATE_POLICIES_RELATIVE);  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Policies\\Google\\Update\\"), kRegKeyGoopdateGroupPolicy);  // NOLINT
}

TEST(OmahaCustomizationTest, Constants_RegistryValues) {
  EXPECT_GU_STREQ(_T("Google Update"), kRunValueName);
}

TEST(OmahaCustomizationTest, Constants_LegacyMsi) {
  EXPECT_STREQ(_T("{A92DAB39-4E2C-4304-9AB6-BC44E68B55E2}"),
               kLegacyHelperInstallerGuid);
}

TEST(OmahaCustomizationTest, Constants_CompatibleMinimumOlderShellVersion) {
  EXPECT_EQ(0x00010003001A0001, kCompatibleMinimumOlderShellVersion);
}

TEST(OmahaCustomizationTest, Constants_BrandCode) {
  EXPECT_STREQ(_T("GGLS"), kDefaultGoogleUpdateBrandCode);
}

TEST(OmahaCustomizationTest, Constants_Addresses) {
  EXPECT_STREQ(_T("www.kingsds.network"), kGoogleHttpServer);
  EXPECT_STREQ(_T("tools.kingsds.network"), kGoopdateServer);
  EXPECT_STREQ(_T("https://updates.kingsds.network/service/update2"),
               kUrlUpdateCheck);
  EXPECT_STREQ(_T("https://updates.kingsds.network/service/update2"), kUrlPing);
  EXPECT_STREQ(_T("https://updates.kingsds.network/service/crash_report"), kUrlCrashReport);
  EXPECT_STREQ(_T("https://kingsds.network/support/installer/?"), kUrlMoreInfo);
  EXPECT_STREQ(_T("https://updates.kingsds.network/service/check2?crx3=true"),
               kUrlCodeRedCheck);
  EXPECT_STREQ(_T("https://updates.kingsds.network/tbproxy/usagestats"),
               kUrlUsageStatsReport);
}

TEST(OmahaCustomizationTest, Constants_Config) {
  EXPECT_GU_STREQ(_T("Software\\Google\\Update\\Shared"), kCiRegKeyShared);
}

TEST(OmahaCustomizationTest, Constants_Debug) {
  EXPECT_GU_STREQ(_T("GoogleUpdate-debug"), kCiDebugDirectory);
}

TEST(OmahaCustomizationTest, Constants_Logging) {
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T(".ini"), kLogConfigFileName);
  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T(".log"), kDefaultLogFileName);
}

// These should not change during customization.
TEST(OmahaCustomizationTest, Constants_ObjectNames_Prefixes) {
  EXPECT_GU_STREQ(_T("Global\\G"), kGlobalPrefix);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_Pipes) {
  EXPECT_GU_STREQ(_T("\\\\.\\pipe\\GoogleCrashServices"), kCrashPipeNamePrefix);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_MutexesAndEvents) {
  EXPECT_STREQ(_T("{C18F3F85-CDD6-4B48-8DE5-98F98C90D77C}"), kSetupMutex);
  EXPECT_STREQ(_T("{3D6E7A03-E2FD-4B99-9973-6CDE9B235AA0}"), kShutdownEvent);
  EXPECT_STREQ(_T("{CC3AF33C-7A64-4D95-BCE1-F40F32DD862C}"),
               kCoreSingleInstance);
  EXPECT_STREQ(_T("{8C1217E3-7EA4-4698-8CCC-79E062C32317}"),
               kCrashHandlerSingleInstance);
  EXPECT_STREQ(_T("{04B54C42-9095-4DA0-B721-F042075A154C}"),
               kUpdateAppsSingleInstance);
  EXPECT_STREQ(_T("%s-{86D25F1C-A1F8-48F5-818D-CAA22C1064BB}"),
               kInstallAppSingleInstance);
  EXPECT_STREQ(_T("{B9D46B77-416A-4985-A29D-1750CB595C7D}"),
               kInstallManagerSerializer);
  EXPECT_STREQ(_T("{99955AB6-659D-4168-8405-9DBF20E82EF6}"),
               kMetricsSerializer);
  EXPECT_STREQ(_T("{93C8DE3A-E199-4156-ACE6-C3342002BA0F}"),
               kRegistryAccessMutex);
}

TEST(OmahaCustomizationTest, Constants_ObjectNames_SharedMemory) {
  EXPECT_GU_STREQ(_T("Global\\GoogleUpdate3"),
                  kGoogleUpdate3SharedMemoryName);
  EXPECT_GU_STREQ(_T("Global\\GoogleUpdateCore"),
                  kGoogleUpdateCoreSharedMemoryName);
}

TEST(OmahaCustomizationTest, Constants_Services) {
  EXPECT_GU_STREQ(_T("gupdate_service_name"), kRegValueServiceName);
  EXPECT_GU_STREQ(_T("gupdatem_service_name"), kRegValueMediumServiceName);
  EXPECT_GU_STREQ(_T("gupdate_task_name_c"), kRegValueTaskNameC);
  EXPECT_GU_STREQ(_T("gupdate_task_name_ua"), kRegValueTaskNameUA);

  EXPECT_GU_STREQ(_T("gupdate"), kServicePrefix);
  EXPECT_GU_STREQ(_T("gupdatem"), kMediumServicePrefix);

  EXPECT_STREQ(MAIN_EXE_BASE_NAME _T(".exe"), kServiceFileName);
}

TEST(OmahaCustomizationTest, Constants_ScheduledTasks) {
  EXPECT_GU_STREQ(_T("GoogleUpdateTaskUser"), kScheduledTaskNameUserPrefix);
  EXPECT_GU_STREQ(_T("GoogleUpdateTaskMachine"), kScheduledTaskNameMachinePrefix);    // NOLINT
}

//
// ConfigManager keys.
//

TEST(OmahaCustomizationTest, ConfigManager_RegistryKeys) {
  const ConfigManager& cm = *ConfigManager::Instance();

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\"), cm.user_registry_clients());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\"), cm.machine_registry_clients());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\"), cm.registry_clients(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\"), cm.registry_clients(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.user_registry_clients_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.machine_registry_clients_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\Clients\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.registry_clients_goopdate(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\Clients\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.registry_clients_goopdate(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\"), cm.user_registry_client_state());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\"), cm.machine_registry_client_state());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\"), cm.registry_client_state(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\"), cm.registry_client_state(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.user_registry_client_state_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.machine_registry_client_state_goopdate());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\ClientState\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.registry_client_state_goopdate(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientState\\{2070893A-B7CF-42FD-9BA1-F00E04A9D766}"), cm.registry_client_state_goopdate(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\ClientStateMedium\\"), cm.machine_registry_client_state_medium());  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\"), cm.user_registry_update());  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\"), cm.machine_registry_update());  // NOLINT
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\Update\\"), cm.registry_update(false));  // NOLINT
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\Update\\"), cm.registry_update(true));  // NOLINT

  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\"), cm.user_registry_google());
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\"), cm.machine_registry_google());
  EXPECT_GU_STREQ(_T("HKCU\\Software\\Google\\"), cm.registry_google(false));
  EXPECT_GU_STREQ(_T("HKLM\\Software\\Google\\"), cm.registry_google(true));
}

TEST(OmahaCustomizationTest, IsInternalUser) {
  if (IsBuildSystem()) {
  // The build system is not configured the same.
  // This may or may not be true in non-Google Update builds.
#ifdef GOOGLE_UPDATE_BUILD
    EXPECT_FALSE(ConfigManager::Instance()->IsInternalUser());
#else
  std::wcout << _T("Did not test IsInternalUser.") << std::endl;
#endif
  } else {
    EXPECT_TRUE(ConfigManager::Instance()->IsInternalUser());
  }
}

//
// Test helpers.
//

TEST(OmahaCustomizationTest, GetGoogleUserPath) {
  EXPECT_STREQ(GetLocalAppDataPath() + PATH_COMPANY_NAME + _T("\\"),
               GetGoogleUserPath());
}

TEST(OmahaCustomizationTest, GetGoogleUpdateUserPath) {
  EXPECT_STREQ(GetLocalAppDataPath() + PATH_COMPANY_NAME + _T("\\")
                                     + PRODUCT_NAME + _T("\\"),
               GetGoogleUpdateUserPath());
}

// Assumes Program Files is in the normal location.
TEST(OmahaCustomizationTest, GetGoogleUpdateMachinePath) {
  CString expected_machine_path;
  EXPECT_SUCCEEDED(GetFolderPath(CSIDL_PROGRAM_FILES | CSIDL_FLAG_DONT_VERIFY,
                                 &expected_machine_path));
  expected_machine_path.Append(_T("\\") PATH_COMPANY_NAME
                               _T("\\") PRODUCT_NAME);
  EXPECT_STREQ(expected_machine_path, GetGoogleUpdateMachinePath());
}

}  // namespace omaha
