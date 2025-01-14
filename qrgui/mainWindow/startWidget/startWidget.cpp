/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "startWidget.h"

#include <QtCore/QSignalMapper>
#include <QtGui/QPainter>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QScrollArea>

#include <qrkernel/settingsManager.h>
#include <qrgui/plugins/pluginManager/editorManagerInterface.h>
#include <qrgui/plugins/pluginManager/qrsMetamodelLoader.h>

#include "mainWindow/mainWindow.h"
#include "mainWindow/errorReporter.h"
#include "styledButton.h"
#include "circleWidget.h"
#include "brandManager/brandManager.h"

using namespace qReal;

StartWidget::StartWidget(MainWindow *mainWindow, ProjectManager *projectManager)
	: mMainWindow(mainWindow)
	, mProjectManager(projectManager)
	, mProjectListSize(SettingsManager::value("recentProjectsLimit", 5).toInt())  // TODO: Why 5?
	, mNewProjectButton(nullptr)
	, mOpenProjectButton(nullptr)
	, mOpenInterpreterButton(nullptr)
	, mCreateInterpreterButton(nullptr)
{
	setStyleSheet(BrandManager::styles()->startTabSubstrateBackgroundStyle());
	QWidget * const mainWidget = createMainWidget();

	QHBoxLayout * const mainLayout = new QHBoxLayout;
	mainLayout->addStretch(1);
	mainLayout->addWidget(mainWidget, 10);
	mainLayout->addStretch(1);
	setLayout(mainLayout);
}

QWidget *StartWidget::createMainWidget()
{
	QWidget * const result = new QWidget;
	result->setStyleSheet(BrandManager::styles()->startTabBackgroundStyle());

	QWidget * const header = createHeader();
	mRecentProjectsWidget = createRecentProjectsWidget();
	QWidget * const projectsManagement = createProjectsManagementWidget();

	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(20);
	QHBoxLayout * contentsLayout = new QHBoxLayout;

	mainLayout->addWidget(header);
	mainLayout->addLayout(contentsLayout);
	mainLayout->setStretch(1, 10);
	if (mRecentProjectsWidget) {
		contentsLayout->addWidget(mRecentProjectsWidget);
	}

	contentsLayout->addWidget(projectsManagement);
	contentsLayout->addWidget(new QWidget());
	contentsLayout->setStretch(0, 2);
	contentsLayout->setStretch(1, 2);
	contentsLayout->setStretch(2, 3);

	result->setLayout(mainLayout);
	return result;
}

QWidget *StartWidget::createHeader()
{
	QLabel * const appName = new QLabel(BrandManager::applicationName());
	appName->setStyleSheet(BrandManager::styles()->startTabLabelLevel1Style());

	QLabel * const appLogo = new QLabel;
	appLogo->setFixedSize(300, 150);
	appLogo->setScaledContents(false);
	appLogo->setPixmap(QPixmap::fromImage(BrandManager::applicationLogo()).scaled(appLogo->size()
			, Qt::KeepAspectRatio, Qt::SmoothTransformation));

	QVBoxLayout * const logoLayout = new QVBoxLayout;
	logoLayout->addWidget(appName);
	logoLayout->addStretch();

	QHBoxLayout * const headerLayout = new QHBoxLayout;
	headerLayout->addLayout(logoLayout);
	headerLayout->addStretch();
	headerLayout->addWidget(appLogo);

	QWidget * const header = new QWidget;
	header->setObjectName("header");
	header->setStyleSheet(BrandManager::styles()->startTabHeaderBackgroundStyle());
	header->setLayout(headerLayout);

	return header;
}

QWidget *StartWidget::createRecentProjectsWidget()
{
	const QString recentProjects = SettingsManager::value("recentProjects").toString();

	QWidget * const result = new QWidget;
	result->setStyleSheet(BrandManager::styles()->startTabRecentProjectsBackgroundStyle());
	result->setLayout(createRecentProjectsList(recentProjects));
	return result;
}

QWidget *StartWidget::createProjectsManagementWidget()
{
	mProjectsManagementLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mProjectsManagementLayout->setSpacing(20);
	mProjectsManagementLayout->setMargin(0);

	mOpenProjectButton = new StyledButton(tr("Open project")
			, ":/mainWindow/images/startTab/open.svg");
	mOpenProjectButton->setObjectName("withIcon");

	connect(mOpenProjectButton, &QPushButton::clicked, this, &StartWidget::openExistingProject);

	const Id theOnlyDiagram = mMainWindow->editorManager().theOnlyDiagram();
	if (!theOnlyDiagram.isNull()) {
		const Id editor = mMainWindow->editorManager().editors()[0];
		const QString diagramIdString = mMainWindow->editorManager().diagramNodeNameString(editor, theOnlyDiagram);

		mNewProjectButton = new StyledButton(tr("New project"), ":/mainWindow/images/startTab/new.svg");
		mNewProjectButton->setObjectName("withIcon");

		QSignalMapper *newProjectMapper = new QSignalMapper(this);
		newProjectMapper->setMapping(mNewProjectButton, diagramIdString);
		connect(mNewProjectButton, SIGNAL(clicked()), newProjectMapper, SLOT(map()));
		connect(newProjectMapper, SIGNAL(mapped(QString)), this, SLOT(createProjectWithDiagram(QString)));
	} else {
		if (!mMainWindow->editorManager().editors().isEmpty()) {
			QWidget * const pluginsWidget = createPluginsList();
			mProjectsManagementLayout->addWidget(pluginsWidget, 1);
		} else {
			mOpenProjectButton->hide();
		}
	}

	mProjectsManagementLayout->addWidget(mOpenProjectButton);
	mProjectsManagementLayout->addWidget(mNewProjectButton);

	QWidget * const result = new QWidget;
	result->setLayout(mProjectsManagementLayout);
	return result;
}

void StartWidget::openRecentProject(const QString &fileName)
{
	mProjectManager->open(fileName);
}

void StartWidget::openExistingProject()
{
	mProjectManager->suggestToOpenExisting();
}

void StartWidget::createProjectWithDiagram(const QString &idString)
{
	mMainWindow->createProject(idString);
}

QLayout *StartWidget::createRecentProjectsList(const QString &recentProjects)
{
	QVBoxLayout * const mainLayout = new QVBoxLayout;
	QVBoxLayout * const recentProjectsLayout = new QVBoxLayout;
	recentProjectsLayout->setContentsMargins(0, 0, 0, 0);

	QLabel * const recentProjectsLabel = new QLabel(tr("Recent projects"));
	recentProjectsLabel->setWordWrap(true);
	recentProjectsLabel->setStyleSheet(BrandManager::styles()->startTabLabelLevel2Style());

	QWidget * const spacer = new QWidget;
	spacer->setFixedHeight(10);

	mainLayout->addWidget(recentProjectsLabel);
	mainLayout->addWidget(spacer);
	mainLayout->addLayout(recentProjectsLayout);

	mainLayout->addStretch(0);

	QSignalMapper * const projectNameMapper = new QSignalMapper(this);
	connect(projectNameMapper, SIGNAL(mapped(QString)), this, SLOT(openRecentProject(QString)));

	int i = 0;
	for (const QString &project : recentProjects.split(";", QString::SkipEmptyParts)) {
		const QString name = project.split("/").last().split("\\").last();
		QPushButton * const projectItem = new StyledButton(name);
		projectItem->setToolTip(project);
		recentProjectsLayout->addWidget(projectItem);

		projectNameMapper->setMapping(projectItem, project);
		connect(projectItem, SIGNAL(clicked()), projectNameMapper, SLOT(map()));

		++i;
		if (i >= mProjectListSize) {
			break;
		}
	}

	return mainLayout;
}

QWidget *StartWidget::createPluginsList()
{
	QWidget * const circleWidget = new CircleWidget(QSize(70, 70), ":/mainWindow/images/startTab/new.svg");
	circleWidget->setStyleSheet(BrandManager::styles()->startTabButtonStyle());

	QVBoxLayout * const innerLayout = new QVBoxLayout;
	innerLayout->addStretch();
	for (const Id &editor : mMainWindow->editorManager().editors()) {
		const Id editorTmpId = Id::loadFromString("qrm:/" + editor.editor());
		for (const Id &diagram : mMainWindow->editorManager().diagrams(editorTmpId)) {
			QWidget * const pluginWidget = createPluginButton(editor, diagram, circleWidget);
			innerLayout->addWidget(pluginWidget);
		}
	}

	innerLayout->addStretch();
	innerLayout->setContentsMargins(0, 0, 0, 0);
	innerLayout->setMargin(0);
	innerLayout->setSpacing(0);

	QWidget *innerWidget = new QWidget;
	innerWidget->setLayout(innerLayout);

	QScrollArea *scrollArea = new QScrollArea;
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setWidgetResizable(true);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidget(innerWidget);

	QHBoxLayout * const mainLayout = new QHBoxLayout;
	mainLayout->addWidget(circleWidget, Qt::AlignCenter);
	mainLayout->addWidget(scrollArea);
	mainLayout->setStretch(0, 0);
	mainLayout->setStretch(1, 10);
	mainLayout->setMargin(0);

	QWidget * const result = new QWidget;
	result->setLayout(mainLayout);

	return result;
}

QWidget *StartWidget::createPluginButton(const Id &editor, const Id &diagram, QWidget * const bindedImage)
{
	const EditorManagerInterface &editorManagerInterface = mMainWindow->editorManager();

	const QString diagramName = editorManagerInterface.diagramName(editor.editor(), diagram.diagram());
	const QString diagramNodeName = editorManagerInterface.diagramNodeName(editor.editor(), diagram.diagram());

	if (diagramNodeName.isEmpty()) {
		return nullptr;
	}

	StyledButton * const result = new StyledButton(tr("Create ") + diagramName);
	result->bindHighlightedOnHover(bindedImage);
	result->setFocusPolicy(Qt::StrongFocus);
	result->setStyleSheet(BrandManager::styles()->startTabButtonStyle());
	result->setToolTip(tr("Editor: ") + editor.editor() + tr("; Diagram: ") + diagram.diagram());

	QSignalMapper *pluginMapper = new QSignalMapper(result);
	pluginMapper->setMapping(result, "qrm:/" + editor.editor() + "/" + diagram.diagram() + "/" + diagramNodeName);
	connect(result, SIGNAL(clicked()), pluginMapper, SLOT(map()));
	connect(pluginMapper, SIGNAL(mapped(QString)), mMainWindow, SLOT(createProject(QString)));

	return result;
}

void StartWidget::openInterpretedDiagram()
{
	const QString fileName = mProjectManager->openFileName(tr("Select file with metamodel to open"));

	if (fileName.isEmpty()) {
		return;
	}

	EditorManagerInterface &editorManager = mMainWindow->editorManager();
	editorManager.setInterpretationMode(true);
	editorManager.unloadAllPlugins();

	QrsMetamodelLoader loader;
	connect(&loader, &QrsMetamodelLoader::errorOccured
			, static_cast<gui::ErrorReporter *>(mMainWindow->errorReporter()), &gui::ErrorReporter::addError);
	const QList<Metamodel *> metamodels = loader.load(fileName);
	for (Metamodel *metamodel : metamodels) {
		editorManager.loadMetamodel(*metamodel);
	}

	/// @todo: Hack for rereading palette, must be done automaticly on plugins set changed!
	mMainWindow->loadEditorPlugins();

	QStringList interpreterDiagramsList;
	for (const Id &editor : editorManager.editors()) {
		for (const Id &diagram : editorManager.diagrams(editor)) {
			const QString diagramNodeName = editorManager.diagramNodeName(editor.editor(), diagram.diagram());
			if (diagramNodeName.isEmpty()) {
				continue;
			}

			interpreterDiagramsList.append("qrm:/" + editor.editor() + "/"
					+ diagram.diagram() + "/" + diagramNodeName);
		}
	}

	mMainWindow->models().repoControlApi().exterminate();
	mMainWindow->models().reinit();
	mMainWindow->loadEditorPlugins();
	if (!interpreterDiagramsList.isEmpty()) {
		mMainWindow->createDiagram(interpreterDiagramsList.first());
	}

	mMainWindow->closeStartTab();
}

void StartWidget::createInterpretedDiagram()
{
	bool ok = false;
	QString name;
	do {
		name = QInputDialog::getText(this, tr("Enter the diagram name:"), tr("diagram name:")
				, QLineEdit::Normal, "", &ok);
	} while (ok && name.isEmpty());

	EditorManagerInterface &editorManager = mMainWindow->editorManager();
	editorManager.setInterpretationMode(true);
	editorManager.unloadAllPlugins();

	if (ok) {
		editorManager.createEditorAndDiagram(name);
		mMainWindow->models().repoControlApi().exterminate();
		mMainWindow->models().reinit();
		mMainWindow->loadEditorPlugins();
		mMainWindow->closeStartTab();
	}
}

void StartWidget::setVisibleForInterpreterButton(const bool visible)
{
	if (!visible) {
		/// @todo: For some reason setVisible on interpreter buttons still leaves them visible.
		/// This surely can be fixed and then setVisible(visible) call must be restored,
		/// but for now working it arround...
		delete mOpenInterpreterButton;
		delete mCreateInterpreterButton;
		mOpenInterpreterButton = nullptr;
		mCreateInterpreterButton = nullptr;
	}

	const int editorsCount = mMainWindow->editorManager().editors().count();
	QList<QPushButton *> toCentralize;
	bool needLayoutHorizontally = false;
	if (visible) {
		needLayoutHorizontally = editorsCount == 0;
		toCentralize << mCreateInterpreterButton << mOpenInterpreterButton;
	} else {
		needLayoutHorizontally = editorsCount == 1 && !mRecentProjectsWidget;
		toCentralize << mNewProjectButton << mOpenProjectButton;
	}

	if (needLayoutHorizontally) {
		for (QPushButton * const button : toCentralize) {
			centralizeButton(button);
		}

		mProjectsManagementLayout->setDirection(QBoxLayout::LeftToRight);
	}
}

void StartWidget::centralizeButton(QPushButton * const styledButton)
{
	if (!styledButton) {
		return;
	}

	QBoxLayout * const layout = static_cast<QBoxLayout *>(styledButton->layout());
	layout->setDirection(QBoxLayout::TopToBottom);
	QWidget * const icon = layout->itemAt(0)->widget();
	QLabel * const label = static_cast<QLabel *>(layout->itemAt(1)->widget());
	label->setAlignment(Qt::AlignHCenter);
	layout->setAlignment(icon, Qt::AlignHCenter | Qt::AlignBottom);
	layout->setAlignment(label, Qt::AlignHCenter | Qt::AlignTop);
	layout->activate();
	layout->update();
	styledButton->update();

	mProjectsManagementLayout->setAlignment(styledButton, Qt::AlignVCenter);
	const int index = mProjectsManagementLayout->indexOf(styledButton);
	mProjectsManagementLayout->setStretch(index, 10000);
}

void StartWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);

	QStyleOption styleOption;
	styleOption.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}
