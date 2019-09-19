/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

#ifndef __qSlicerModelsModuleWidget_h
#define __qSlicerModelsModuleWidget_h

// CTK includes
#include "ctkVTKObject.h"

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerModelsModuleExport.h"

class qSlicerModelsModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLSelectionNode;

/// \ingroup Slicer_QtModules_Models
class Q_SLICER_QTMODULES_MODELS_EXPORT qSlicerModelsModuleWidget : public qSlicerAbstractModuleWidget
{
  Q_OBJECT
  QVTK_OBJECT

public:
  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerModelsModuleWidget(QWidget *parent=nullptr);
  ~qSlicerModelsModuleWidget() override;

  void enter() override;
  void exit() override;
  bool setEditedNode(vtkMRMLNode* node, QString role = QString(), QString context = QString()) override;

  vtkMRMLSelectionNode* getSelectionNode();

public slots:
  void setMRMLScene(vtkMRMLScene* scene) override;

  /// Set current node associated to the selected subject hierarchy item to the widgets
  void setDisplaySelectionFromSubjectHierarchyItem(vtkIdType itemID);

  void includeFiberBundles(bool include);
  void onDisplayClassChanged(int index);
  void onClippingConfigurationButtonClicked();
  void onDisplayNodeChanged();
  void onClipSelectedModelToggled(bool);

  static void onMRMLSceneEvent(vtkObject* vtk_obj, unsigned long event,
                               void* client_data, void* call_data);

  /// hide/show all the models in the scene
  void hideAllModels();
  void showAllModels();

protected slots:
  /// Called when a subject hierarchy item is modified.
  /// Updates current item selection to reflect changes in item (such as display node creation)
  void onSubjectHierarchyItemModified(vtkObject* caller, void* callData);

protected:
  void setup() override;

  void updateWidgetFromSelectionNode();

protected:
  QScopedPointer<qSlicerModelsModuleWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerModelsModuleWidget);
  Q_DISABLE_COPY(qSlicerModelsModuleWidget);
};

#endif
