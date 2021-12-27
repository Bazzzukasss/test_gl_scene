#pragma once

#include "gl_scene.h"
#include "gl_scene_view.h"
#include <QMainWindow>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

 public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

 private:
    Ui::MainWindow* ui;
    gl_scene::Scene::Ptr mScene;
    gl_scene::Item::Ptr mCameraNearItem;
    gl_scene::Item::Ptr mCameraFarItem;
    gl_scene::Item::Ptr mCameraProjItem;
    gl_scene::Item::Ptr mCameraItem;
    gl_scene::Item::Ptr mGridItem;
    gl_scene::Manipulator::Ptr mManipulator;
    QTimer mTimer;
    uint radius{1};
    int sign{1};
    uint itemIndex{0};

    void updateCamera(GLSceneView* view);

    void addCamera();
    void addGrid();
    void addPath(const gl_scene::Point3Pack& path);
    void addMutableItems(int count);
    void addTexturedItem();
    void addItems(int count, bool is_fixed_items, bool is_mutable_items);
};
