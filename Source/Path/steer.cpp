// Fill out your copyright notice in the Description page of Project Settings.


#include "steer.h"
#include "Math/Vector.h"

steer::steer()
{	
	
}

steer::~steer()
{
}

FVector steer::truncate(FVector v, const float& max)
{
	if (v.Size() > max) 
	{
		v.Normalize();
		return v;
	}
	return v;
}

FRotator steer::calculateDirection()
{
	FVector new_forward = velocity;
	new_forward.Normalize();
	FVector approximate_up = orientation.Vector();
	approximate_up.Normalize();
	FVector new_side = FVector::CrossProduct(new_forward,approximate_up);
	FVector new_up = FVector::CrossProduct(new_forward,new_side);
	orientation = new_up.ToOrientationRotator();
	return orientation;
}

FVector steer::seek(const FVector target)
{
	FVector direction = target - position;
	direction.Normalize();
	FVector desired_velocity = direction * max_speed;
	return desired_velocity - velocity;
}

FVector steer::flee(const FVector target)
{
	return seek(target) * -1;
}

FVector steer::pursue(const FVector target)
{
	return FVector();
}

