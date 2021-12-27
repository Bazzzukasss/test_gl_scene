#include "main_window.h"
#include "ui_main_window.h"
#include "gl_scene_generator.h"
#include "data.h"
#include <cmath>

using namespace gl_scene;
using namespace gl_scene::defaults;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mScene       = std::make_shared<Scene>();
    mManipulator = std::make_shared<StandartManipulator>(FreeCamera);

    addGrid();
    addCamera();

    addItems(100, true, true);
    addMutableItems(10);
    addPath({{0, 0, 0}, {0, 5, 0}, {5, 8, 0}, {10, 7, 0}, {15, 7, 0}, {13, 12, 0}, {10, 9, 0}, {5, 9, 0}});
    addTexturedItem();

    ui->mView->setScene(mScene);
    ui->mView->setManipulator(mManipulator);
    ui->mView->setBackgroundColor(Qt::white);

    ui->mTopView->setScene(mScene);
    ui->mTopView->setManipulator(mManipulator);
    ui->mTopView->setBackgroundColor(Qt::white);
    ui->mTopView->camera().move(Camera::MovementDirection::kForward, -80);

    QObject::connect(ui->mView, &GLSceneView::signalCameraChanged, [&]() {
        updateCamera(ui->mView);
        ui->mTopView->update();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCamera(GLSceneView* view)
{
    Point2Pack rect = {
        {0, 0},
        {view->width(), 0},
        {view->width(), view->height()},
        {0, view->height()},
    };
    const auto& pointsNear = view->camera().toWorldCoordinates(rect, 0.01f);
    const auto& pointsFar  = view->camera().toWorldCoordinates(rect, 0.9999f);
    const auto& pointsProj = view->camera().toWorldXYCoordinates(rect, 0.0f);

    mCameraNearItem->vertexPack = Mesh(pointsNear, false).getVertices();
    mCameraFarItem->vertexPack  = Mesh(pointsFar, false).getVertices();
    mCameraProjItem->vertexPack = Mesh(pointsProj, false).getVertices();
    mCameraItem->vertexPack     = Mesh(GENERATE(FigureStripe{pointsNear, pointsFar})).getVertices();
}

void MainWindow::addCamera()
{
    mCameraNearItem = mScene->addItem({VertexPack{}, Qt::green, 0, {GL_LINE_LOOP, 1.0f}, pipes::id::k2D});
    mCameraFarItem  = mScene->addItem({VertexPack{}, Qt::blue, 0, {GL_LINE_LOOP, 1.0f}, pipes::id::k2D});
    mCameraProjItem = mScene->addItem({VertexPack{}, Qt::red, 0, {GL_LINE_LOOP, 1.0f}, pipes::id::k2D});
    mCameraItem     = mScene->addItem({VertexPack{}, Qt::black, 0, {GL_LINES, 1.0f}, pipes::id::k2D});
}

void MainWindow::addGrid()
{
    mGridItem = mScene->addItem({meshes::id::kGrid, Qt::gray, 0, {GL_LINES, 1.0f}, pipes::id::k2D});
}

void MainWindow::addItems(int count, bool is_fixed_items, bool is_mutable_items)
{
    Item::Ptr item;
    const int w{static_cast<int>(std::sqrt(count))};
    const int step{4};

    for (int i{0}; i < count; i++)
    {
        int x = i / w;
        int y = i % w;
        // Fixed geometry items
        if (is_fixed_items)
        {
            item =
                mScene->addItem({meshes::id::kCylinder, Qt::blue, ++itemIndex, {GL_TRIANGLES, 1.0f}, pipes::id::k3D});
            item->transformation.translate(x * 2 * step, y * 2 * step, 0);
            item = mScene->addItem({meshes::id::kCube, Qt::blue, ++itemIndex, {GL_TRIANGLES, 1.0f}, pipes::id::k2D});
            item->transformation.translate((x * 2 + 1) * step, y * 2 * step, 0);
        }

        // Mutable geometry items
        if (is_mutable_items)
        {
            item = mScene->addItem(
                {meshes::kSphere.getVertices(), Qt::red, ++itemIndex, {GL_TRIANGLES, 1.0f}, pipes::id::k3D});
            item->transformation.translate(x * 2 * step, (y * 2 + 1) * step, 0);
            item = mScene->addItem(
                {meshes::kConus.getVertices(), Qt::red, ++itemIndex, {GL_TRIANGLES, 1.0f}, pipes::id::k2D});
            item->transformation.translate((x * 2 + 1) * step, (y * 2 + 1) * step, 0);
        }
    }
}

void MainWindow::addMutableItems(int count)
{
    std::vector<Item::Ptr> items;
    const int w{static_cast<int>(std::sqrt(count))};
    const int step{4};

    for (int i{0}; i < count; ++i)
    {
        int x     = i / w;
        int y     = i % w;
        auto item = mScene->addItem(
            {meshes::kSphere.getVertices(), Qt::green, ++itemIndex, {GL_TRIANGLES, 1.0f}, pipes::id::k3D});
        item->transformation.translate(x * step, y * step, 2.0f);
        items.push_back(item);
    }

    QObject::connect(&mTimer, &QTimer::timeout, [=]() {
        Mesh sphere{GENERATE(FigureSphere{radius / 5.0f, radius * 4, radius * 2}), 0.0f};
        for (auto& item : items)
        {
            item->vertexPack = sphere.getVertices();
        }

        if (radius >= 10)
        {
            sign = -1;
        }

        if (radius <= 1)
        {
            sign = 1;
        }

        radius += sign;
        ui->mView->update();
        ui->mTopView->update();
    });

    mTimer.start(100);
}

void MainWindow::addTexturedItem()
{
    VertexPack vertexes = {
        {0, 0, 5, 0, 0, 1, 0, 0},     {0, 100, 5, 0, 0, 1, 0, 1}, {100, 100, 5, 0, 0, 1, 1, 1},

        {100, 100, 5, 0, 0, 1, 1, 1}, {100, 0, 5, 0, 0, 1, 1, 0}, {0, 0, 5, 0, 0, 1, 0, 0},
    };

    auto item = mScene->addItem({vertexes,
                                 Qt::blue,
                                 ++itemIndex,
                                 {GL_TRIANGLES, 0.5f, {1.0f, {GL_BLEND}, {GL_CULL_FACE}}},
                                 pipes::id::k2DTextured});
    QTimer::singleShot(0, [=]() {
        item->texture = std::make_shared<QOpenGLTexture>(QImage(":/images/viztool.png").mirrored());
        item->texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        item->texture->setMagnificationFilter(QOpenGLTexture::Linear);
    });
}

void MainWindow::addPath(const Point3Pack& path)
{
    auto item1 = mScene->addItem({Mesh(path, false).getVertices(),
                                  Qt::red,
                                  ++itemIndex,
                                  {GL_LINE_STRIP, 1.0f, {1.0f, {}, {GL_CULL_FACE}}},
                                  pipes::id::k2D});
    item1->transformation.translate(0, 0, 0.002f);

    auto item2 = mScene->addItem({Mesh(GENERATE(FigurePath{path, 1.0f})).getVertices(),
                                  Qt::blue,
                                  ++itemIndex,
                                  {GL_TRIANGLES, 1.0f, {1.0f, {}, {GL_CULL_FACE}}},
                                  pipes::id::k2D});
    item2->transformation.translate(0, 0, 0.003f);
}
