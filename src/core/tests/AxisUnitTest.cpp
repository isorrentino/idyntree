/*
 * Copyright (C) 2015 Fondazione Istituto Italiano di Tecnologia
 * Authors: Silvio Traversaro
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <iDynTree/Core/Axis.h>
#include <iDynTree/Core/Transform.h>
#include <iDynTree/Core/Utils.h>
#include <iDynTree/Core/TestUtils.h>
#include <iDynTree/Core/Twist.h>

#include <cstdio>
#include <cstdlib>

using namespace iDynTree;

void validateRotationAroundArbitraryAxis(Axis & ax, double theta)
{
    Transform notRotated_H_rotated = ax.getRotationTransform(theta);
    Transform notRotated_H_rotated_validation =
        Transform(Rotation::Identity(),ax.getOrigin())
            *Transform(Rotation::RotAxis(ax.getDirection(),theta),Position::Zero())
            *Transform(Rotation::Identity(),-ax.getOrigin());

    assertTransformsAreEqual(notRotated_H_rotated,notRotated_H_rotated_validation);
}

void validateRotationAroundZAxis(Axis & ax, double theta)
{
    Transform notRotated_H_rotated = ax.getRotationTransform(theta);
    Transform notRotated_H_rotated_validation =
        Transform(Rotation::Identity(),ax.getOrigin())
            *Transform(Rotation::RotZ(theta),Position())
            *Transform(Rotation::Identity(),-ax.getOrigin());

    assertTransformsAreEqual(notRotated_H_rotated,notRotated_H_rotated_validation);
}

void validateInvarianceOfTwist(const Axis & ax, const Transform & trans, double dtheta)
{
    Twist t = ax.getRotationTwist(dtheta);

    Twist t_trans = trans*t;

    Twist t_trans_check = (trans*ax).getRotationTwist(dtheta);

    ASSERT_EQUAL_SPATIAL_MOTION(t_trans,t_trans_check);
}




int main()
{
    // test setters and getters
    Axis ax;

    Direction dir(1,2,3);
    Position  origin(3,2,1);

    ax.setDirection(dir);
    ax.setOrigin(origin);

    assertVectorAreEqual(ax.getDirection(),dir);
    assertVectorAreEqual(ax.getOrigin(),origin);

    // test transforms
    Transform trans(Rotation::RPY(0.5,0.4,-0.3),Position(3,4,5));

    assertVectorAreEqual((trans*ax).getDirection(),trans*dir);
    assertVectorAreEqual((trans*ax).getOrigin(),trans*origin);

    // Test rotation around the axis
    Axis axRot;

    Direction dirRot(0,0,1);
    Position  originRot(1,0,0);

    axRot.setDirection(dirRot);
    axRot.setOrigin(originRot);

    printf("Validate rotation around arbitrary axis\n");
    validateRotationAroundArbitraryAxis(ax,2.0);
    /*
    printf("Validate rotation around Z axis\n");
    validateRotationAroundZAxis(axRot,4.0);
    printf("Validate invariance of twist of rotation around this axis");
    validateInvarianceOfTwist(ax,trans,1.0);
    validateInvarianceOfTwist(axRot,trans,1.0);*/


    return EXIT_SUCCESS;
}