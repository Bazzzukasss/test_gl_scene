#include "data.h"
#include "gl_scene_types.h"

using namespace gl_scene;

const Vec3 kWorldUp{0.0f, 0.0f, 1.0f};
const float kSpeed{5.0f};
const float kSensitivity{0.25f};
const float kZoom{1.0f};
const Vec3 kScale{1.0f, 1.0f, 1.0f};
const ProjectionOrtho kOrthoProjection{-150.0f, 150.0f, -50.0f, 250.0f, 0.0f, 250.0f, 1.0};
const ProjectionPerspective kPerspectiveProjection{45.0f, 0.1f, 800.0f, 1.0f};
const Camera::RangeLimits kRangeLimits{{true, -300.0f, 300.0f}, {true, -200.0f, 300.0f}, {true, 5.0f, 200.0f},
                                       {true, 1.0f, 10.0f},     {true, 0.0f, 360.0f},    {true, -89.0f, 0.0f},
                                       {true, 0.02f, 1.0f}};
const Camera::RangeLimits kOrthoRangeLimits{{true, -300.0f, 300.0f}, {true, -200.0f, 300.0f}, {true, 0.0f, 200.0f},
                                            {true, 1.0f, 10.0f},     {true, 0.0f, 360.0f},    {true, -89.0f, 0.0f},
                                            {true, 0.02f, 1.0f}};

const Camera::RangeLimits kFixedPosRangeLimits{{true, -300.0f, 300.0f}, {true, -200.0f, 300.0f}, {true, 0.1f, 200.0f},
                                               {true, 1.0f, 10.0f},     {true, 0.0f, 360.0f},    {true, -89.0f, 0.0f}};

const Camera FreeCamera{{0.0f, -50.0f, 100.0f},
                        kWorldUp,
                        90.0f,
                        -45.0f,
                        kSpeed,
                        kSensitivity,
                        kZoom,
                        kScale,
                        Projection::Type::kPerspective,
                        kPerspectiveProjection,
                        kOrthoProjection,
                        kRangeLimits};

const Camera TopCamera{{0.0f, 25.0f, 100.0f},
                       kWorldUp,
                       90.0f,
                       -89.999f,
                       kSpeed,
                       kSensitivity,
                       kZoom,
                       {0.4f, 0.4f, 1.0f},
                       Projection::Type::kOrtho,
                       kPerspectiveProjection,
                       {-100.0f, 100.0f, -100.0f, 100.0f, 0.0f, 250.0f, 1.0},
                       kRangeLimits};

const Camera BackPCamera{{0.0f, -5.0f, 3.0f},
                         kWorldUp,
                         90.0f,
                         -7.0f,
                         kSpeed,
                         kSensitivity,
                         kZoom,
                         kScale,
                         Projection::Type::kPerspective,
                         kPerspectiveProjection,
                         kOrthoProjection,
                         kRangeLimits};

const Camera SidePCamera{{60.0f, 50.0f, 30.0f},
                         kWorldUp,
                         180.0f,
                         -20.0f,
                         kSpeed,
                         kSensitivity,
                         kZoom,
                         kScale,
                         Projection::Type::kPerspective,
                         kPerspectiveProjection,
                         kOrthoProjection,
                         kRangeLimits};

const Camera BackOCamera{{0.0f, 0.0f, 0.0f},
                         kWorldUp,
                         90.0f,
                         0.0f,
                         kSpeed,
                         kSensitivity,
                         kZoom,
                         kScale,
                         Projection::Type::kOrtho,
                         kPerspectiveProjection,
                         {-25.0f, 25.0f, -25.0f, 25.0f, -3000.0f, 3000.0f, 1.0},
                         kOrthoRangeLimits};

const Camera SideOCamera{{0.0f, 40.0f, 0.0f},
                         kWorldUp,
                         180.0f,
                         0.0f,
                         kSpeed,
                         kSensitivity,
                         kZoom,
                         kScale,
                         Projection::Type::kOrtho,
                         kPerspectiveProjection,
                         {-25.0f, 25.0f, -25.0f, 25.0f, -3000.0f, 3000.0f, 1.0},
                         kOrthoRangeLimits};

const Camera CabinCamera{{0.0f, 0.8f, 1.3f},
                         kWorldUp,
                         90.0f,
                         -7.0f,
                         kSpeed,
                         kSensitivity / 4,
                         kZoom,
                         kScale,
                         Projection::Type::kPerspective,
                         kPerspectiveProjection,
                         kOrthoProjection,
                         kFixedPosRangeLimits};

const Camera FrontCamera{{0.0f, 1.0f, 2.5f},
                         kWorldUp,
                         90.0f,
                         -14.0f,
                         kSpeed,
                         kSensitivity / 4,
                         kZoom,
                         kScale,
                         Projection::Type::kPerspective,
                         kPerspectiveProjection,
                         kOrthoProjection,
                         kFixedPosRangeLimits};
