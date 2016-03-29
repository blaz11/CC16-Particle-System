#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T20:59:49
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ParticlesSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp \
    Libraries/glm/detail/glm.cpp \
    camera.cpp \
    shader.cpp \
    pipeobject.cpp

HEADERS  += mainwindow.h \
    openglwidget.h \
    Libraries/glm/detail/_features.hpp \
    Libraries/glm/detail/_fixes.hpp \
    Libraries/glm/detail/_noise.hpp \
    Libraries/glm/detail/_swizzle.hpp \
    Libraries/glm/detail/_swizzle_func.hpp \
    Libraries/glm/detail/_vectorize.hpp \
    Libraries/glm/detail/func_common.hpp \
    Libraries/glm/detail/func_exponential.hpp \
    Libraries/glm/detail/func_geometric.hpp \
    Libraries/glm/detail/func_integer.hpp \
    Libraries/glm/detail/func_matrix.hpp \
    Libraries/glm/detail/func_packing.hpp \
    Libraries/glm/detail/func_trigonometric.hpp \
    Libraries/glm/detail/func_vector_relational.hpp \
    Libraries/glm/detail/intrinsic_common.hpp \
    Libraries/glm/detail/intrinsic_exponential.hpp \
    Libraries/glm/detail/intrinsic_geometric.hpp \
    Libraries/glm/detail/intrinsic_integer.hpp \
    Libraries/glm/detail/intrinsic_matrix.hpp \
    Libraries/glm/detail/intrinsic_trigonometric.hpp \
    Libraries/glm/detail/intrinsic_vector_relational.hpp \
    Libraries/glm/detail/precision.hpp \
    Libraries/glm/detail/setup.hpp \
    Libraries/glm/detail/type_float.hpp \
    Libraries/glm/detail/type_gentype.hpp \
    Libraries/glm/detail/type_half.hpp \
    Libraries/glm/detail/type_int.hpp \
    Libraries/glm/detail/type_mat.hpp \
    Libraries/glm/detail/type_mat2x2.hpp \
    Libraries/glm/detail/type_mat2x3.hpp \
    Libraries/glm/detail/type_mat2x4.hpp \
    Libraries/glm/detail/type_mat3x2.hpp \
    Libraries/glm/detail/type_mat3x3.hpp \
    Libraries/glm/detail/type_mat3x4.hpp \
    Libraries/glm/detail/type_mat4x2.hpp \
    Libraries/glm/detail/type_mat4x3.hpp \
    Libraries/glm/detail/type_mat4x4.hpp \
    Libraries/glm/detail/type_vec.hpp \
    Libraries/glm/detail/type_vec1.hpp \
    Libraries/glm/detail/type_vec2.hpp \
    Libraries/glm/detail/type_vec3.hpp \
    Libraries/glm/detail/type_vec4.hpp \
    Libraries/glm/gtc/bitfield.hpp \
    Libraries/glm/gtc/color_space.hpp \
    Libraries/glm/gtc/constants.hpp \
    Libraries/glm/gtc/epsilon.hpp \
    Libraries/glm/gtc/integer.hpp \
    Libraries/glm/gtc/matrix_access.hpp \
    Libraries/glm/gtc/matrix_integer.hpp \
    Libraries/glm/gtc/matrix_inverse.hpp \
    Libraries/glm/gtc/matrix_transform.hpp \
    Libraries/glm/gtc/noise.hpp \
    Libraries/glm/gtc/packing.hpp \
    Libraries/glm/gtc/quaternion.hpp \
    Libraries/glm/gtc/random.hpp \
    Libraries/glm/gtc/reciprocal.hpp \
    Libraries/glm/gtc/round.hpp \
    Libraries/glm/gtc/type_precision.hpp \
    Libraries/glm/gtc/type_ptr.hpp \
    Libraries/glm/gtc/ulp.hpp \
    Libraries/glm/gtc/vec1.hpp \
    Libraries/glm/gtx/associated_min_max.hpp \
    Libraries/glm/gtx/bit.hpp \
    Libraries/glm/gtx/closest_point.hpp \
    Libraries/glm/gtx/color_space.hpp \
    Libraries/glm/gtx/color_space_YCoCg.hpp \
    Libraries/glm/gtx/common.hpp \
    Libraries/glm/gtx/compatibility.hpp \
    Libraries/glm/gtx/component_wise.hpp \
    Libraries/glm/gtx/dual_quaternion.hpp \
    Libraries/glm/gtx/euler_angles.hpp \
    Libraries/glm/gtx/extend.hpp \
    Libraries/glm/gtx/extented_min_max.hpp \
    Libraries/glm/gtx/fast_exponential.hpp \
    Libraries/glm/gtx/fast_square_root.hpp \
    Libraries/glm/gtx/fast_trigonometry.hpp \
    Libraries/glm/gtx/gradient_paint.hpp \
    Libraries/glm/gtx/handed_coordinate_space.hpp \
    Libraries/glm/gtx/hash.hpp \
    Libraries/glm/gtx/integer.hpp \
    Libraries/glm/gtx/intersect.hpp \
    Libraries/glm/gtx/io.hpp \
    Libraries/glm/gtx/log_base.hpp \
    Libraries/glm/gtx/matrix_cross_product.hpp \
    Libraries/glm/gtx/matrix_decompose.hpp \
    Libraries/glm/gtx/matrix_interpolation.hpp \
    Libraries/glm/gtx/matrix_major_storage.hpp \
    Libraries/glm/gtx/matrix_operation.hpp \
    Libraries/glm/gtx/matrix_query.hpp \
    Libraries/glm/gtx/matrix_transform_2d.hpp \
    Libraries/glm/gtx/mixed_product.hpp \
    Libraries/glm/gtx/norm.hpp \
    Libraries/glm/gtx/normal.hpp \
    Libraries/glm/gtx/normalize_dot.hpp \
    Libraries/glm/gtx/number_precision.hpp \
    Libraries/glm/gtx/optimum_pow.hpp \
    Libraries/glm/gtx/orthonormalize.hpp \
    Libraries/glm/gtx/perpendicular.hpp \
    Libraries/glm/gtx/polar_coordinates.hpp \
    Libraries/glm/gtx/projection.hpp \
    Libraries/glm/gtx/quaternion.hpp \
    Libraries/glm/gtx/range.hpp \
    Libraries/glm/gtx/raw_data.hpp \
    Libraries/glm/gtx/rotate_normalized_axis.hpp \
    Libraries/glm/gtx/rotate_vector.hpp \
    Libraries/glm/gtx/scalar_multiplication.hpp \
    Libraries/glm/gtx/scalar_relational.hpp \
    Libraries/glm/gtx/simd_mat4.hpp \
    Libraries/glm/gtx/simd_quat.hpp \
    Libraries/glm/gtx/simd_vec4.hpp \
    Libraries/glm/gtx/spline.hpp \
    Libraries/glm/gtx/std_based_type.hpp \
    Libraries/glm/gtx/string_cast.hpp \
    Libraries/glm/gtx/transform.hpp \
    Libraries/glm/gtx/transform2.hpp \
    Libraries/glm/gtx/type_aligned.hpp \
    Libraries/glm/gtx/vector_angle.hpp \
    Libraries/glm/gtx/vector_query.hpp \
    Libraries/glm/gtx/wrap.hpp \
    Libraries/glm/common.hpp \
    Libraries/glm/exponential.hpp \
    Libraries/glm/ext.hpp \
    Libraries/glm/fwd.hpp \
    Libraries/glm/geometric.hpp \
    Libraries/glm/glm.hpp \
    Libraries/glm/integer.hpp \
    Libraries/glm/mat2x2.hpp \
    Libraries/glm/mat2x3.hpp \
    Libraries/glm/mat2x4.hpp \
    Libraries/glm/mat3x2.hpp \
    Libraries/glm/mat3x3.hpp \
    Libraries/glm/mat3x4.hpp \
    Libraries/glm/mat4x2.hpp \
    Libraries/glm/mat4x3.hpp \
    Libraries/glm/mat4x4.hpp \
    Libraries/glm/matrix.hpp \
    Libraries/glm/packing.hpp \
    Libraries/glm/trigonometric.hpp \
    Libraries/glm/vec2.hpp \
    Libraries/glm/vec3.hpp \
    Libraries/glm/vec4.hpp \
    Libraries/glm/vector_relational.hpp \
    drawableobject.h \
    camera.h \
    shader.h \
    pipeobject.h

FORMS    += mainwindow.ui

DISTFILES += \
    fragment_shader.glsl \
    vertex_shader.glsl

win32: LIBS += -L$$PWD/Libraries/ -lfreeglut

INCLUDEPATH += $$PWD/Libraries
DEPENDPATH += $$PWD/Libraries
