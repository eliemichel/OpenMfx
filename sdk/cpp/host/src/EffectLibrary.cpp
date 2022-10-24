/*
 * Copyright 2019 Elie Michel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "EffectLibrary.h"
#include "Allocator.h"
#include "macros.h"

#include <ofxMeshEffect.h>

#include <cstring>
#include <cstdio>

#ifdef _WIN32
#  define PATH_DIR_SEP '\\'
#else // _WIN32
#  define PATH_DIR_SEP '/'
#endif // _WIN32

namespace OpenMfx {

bool EffectLibrary::load(const char* ofx_filepath) {
    LOG("Loading OFX plug-ins from %s.\n", ofx_filepath);

    if (false == initBinary(ofx_filepath)) {
        LOG("Could not init binary.\n");
        unload();
        return false;
    }

    if (nullptr != m_procedures.setBundleDirectory) {
        char* bundle_directory = Allocator::malloc<char>(strlen(ofx_filepath) + 1, "bundle directory");
        strcpy(bundle_directory, ofx_filepath);
        *strrchr(bundle_directory, PATH_DIR_SEP) = '\0';
        m_procedures.setBundleDirectory(bundle_directory);
        Allocator::free(bundle_directory);
    }

    initPlugins();

    return true;
}

void EffectLibrary::unload() {
    if (nullptr != m_handle) {
        binary_close(m_handle);
        m_handle = nullptr;
    }
}

int EffectLibrary::pluginCount() const {
    return static_cast<int>(m_plugins.size());
}

EffectLibrary::Status EffectLibrary::pluginStatus(int pluginIndex) const {
    return m_plugins[pluginIndex].second;
}

OfxPlugin* EffectLibrary::plugin(int pluginIndex) const {
    return m_plugins[pluginIndex].first;
}

bool EffectLibrary::initBinary(const char* ofx_filepath) {
    // Open ofx binary
    m_handle = binary_open(ofx_filepath);
    if (nullptr == m_handle) {
        return false;
    }

    // Get procedures
    m_procedures.getNumberOfPlugins =
        (OfxGetNumberOfPluginsFunc)binary_get_proc(m_handle, "OfxGetNumberOfPlugins");
    m_procedures.getPlugin =
        (OfxGetPluginFunc)binary_get_proc(m_handle, "OfxGetPlugin");
    m_procedures.setBundleDirectory =
        (OfxSetBundleDirectoryFunc)binary_get_proc(m_handle, "OfxSetBundleDirectory");

    return nullptr != m_procedures.getNumberOfPlugins && nullptr != m_procedures.getPlugin;
}

void EffectLibrary::initPlugins() {
    int n = m_procedures.getNumberOfPlugins();
    LOG("Found %d plugins.\n", n);

    for (int i = 0; i < n; ++i) {
        OfxPlugin* plugin;
        plugin = m_procedures.getPlugin(i);
        LOG("Plugin #%d: %s (API %s, version %d)\n", i, plugin->pluginIdentifier, plugin->pluginApi, plugin->apiVersion);

        // API/Version check
        if (0 != strcmp(plugin->pluginApi, kOfxMeshEffectPluginApi)) {
            LOG("Unsupported plugin API: %s (expected %s)", plugin->pluginApi, kOfxMeshEffectPluginApi);
            continue;
        }
        if (plugin->apiVersion != kOfxMeshEffectPluginApiVersion) {
            LOG("Plugin API version mismatch: %d found, but %d expected", plugin->apiVersion, kOfxMeshEffectPluginApiVersion);
            continue;
        }

        LOG("Plugin #%d in binary is #%zu in plugin registry\n", i, m_plugins.size());
        m_plugins.push_back({ plugin, Status::NotLoaded });
    }

    LOG("Found %zu supported plugins.\n", m_plugins.size());
}

} // namespace OpenMfx
