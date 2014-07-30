#pragma once

#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtCore/QObject>
#include <QtCore/QMap>

#include "qrutils/utilsDeclSpec.h"

namespace qReal {

class QRUTILS_EXPORT CommonPluginManager
{
public:
	/// constructor of class CommonPluginManager
	/// @param applicationDirPath - path to qrgui.exe
	/// @param additionalPart - path to folder with plugins, usually "bin/plugins", for robots can be folder inside plugins folder
	CommonPluginManager(
			QString const &applicationDirPath
			, QString const &additionalPart = "plugins"
			);
	~CommonPluginManager();

	/// deletes all loaders
	void deleteAllLoaders();
	/// returns list of all found plugins if succeed and empty list otherwise
	QList<QObject *> allLoadedPlugins();
	/// returns plugin found by name if succeed and nothing otherwise
	/// and error message, if failed
	QPair<QObject *, QString> pluginLoadedByName(QString const &pluginName);

	/// unloads plugins, given filename
	/// first member in pair is error message
	/// second member is true if plugin was unloaded
	/// trird member is true if loader was found
	QPair<QString, QPair<bool, bool> > unloadPlugin(QString const &pluginName);

	/// returns fileName by given object
	QString fileName(QObject *plugin) const;

private:
	/// directory to loaded plugins
	QDir mPluginsDir;
	/// map from name to loader
	QMap<QString, QPluginLoader *> mLoaders;
	/// map from fileName to plugin
	QMap<QString, QObject *> mNameAndObject;
	/// path to application directory, used to count path to loaded plugins
	QString mApplicationDirectoryPath;
	/// "plugins" if we're trying to load plugins from "bin/plugins"
	/// for robots it can be "plugins/kitPlugins", for example
	QString mAdditionalPart;
};
}
