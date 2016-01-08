// Copyright 2016 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_RUNTIME_BROWSER_XWALK_CONTENT_SETTINGS_H_
#define XWALK_RUNTIME_BROWSER_XWALK_CONTENT_SETTINGS_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "base/prefs/pref_service.h"
#include "base/prefs/json_pref_store.h"
#include "components/content_settings/core/browser/host_content_settings_map.h"

namespace xwalk {

// This class (a singleton) manages the content settings for XWalk.
// It writes them on disk in the user data under the filename Preferences.
// These settings are persistent across runs.
class XWalkContentSettings {
 public:
  static XWalkContentSettings* GetInstance();
  // This function needs to be called on startup while I/O is allowed.
  void Init();
  void Shutdown();
  void SetPermission(
  ContentSettingsType type,
      const GURL& requesting_origin,
      const GURL& embedding_origin,
      ContentSetting content_setting);
  ContentSetting GetPermission(
      ContentSettingsType type,
      const GURL& requesting_origin,
      const GURL& embedding_origin);

 private:
  XWalkContentSettings();
  ~XWalkContentSettings();

  base::FilePath GetPrefFilePathFromPath(const base::FilePath& path);

  scoped_ptr<PrefService> pref_service_;
  scoped_refptr<user_prefs::PrefRegistrySyncable> pref_registry_;
  scoped_refptr<JsonPrefStore> pref_store_;
  scoped_refptr<base::SequencedTaskRunner> sequenced_task_runner_;
  scoped_refptr<HostContentSettingsMap> host_content_settings_map_;
  friend struct DefaultSingletonTraits<XWalkContentSettings>;

  DISALLOW_COPY_AND_ASSIGN(XWalkContentSettings);
};

}  // namespace xwalk

#endif  // XWALK_RUNTIME_BROWSER_XWALK_CONTENT_SETTINGS_H_
