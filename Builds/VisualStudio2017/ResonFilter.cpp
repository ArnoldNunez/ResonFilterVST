#include "ResonFilter.h"

#include <cmath>

/// The mathematical value of pi
const double PI = 3.14159265358979323846;

CResonFilter::CResonFilter()
{
	mFreq = 0.045351f;
	mBand = 0.01f;
	mGain = 1.0f;
}


CResonFilter::~CResonFilter()
{
}

void CResonFilter::BlockProcess(float * leftSamples, float * rightSamples, int numSamples)
{
	double R = 1.0 - mBand / 2.0;
	double cosTheta = (2.0 * R * cos(2.0 * PI * mFreq)) / (1 + pow(R, 2));
	double sinTheta = sqrt(1 - pow(cosTheta, 2));
	double A = (1 - pow(R, 2)) * sinTheta;

	// Add gain factor
	A = A * mGain;

	// TODO: Should this be here?
	mY1L = 0;
	mY1R = 0;
	mY2L = 0;
	mY2R = 0;

	for (int i = 0; i < numSamples; ++i)
	{
		// Filter calculation
		leftSamples[i] = A * leftSamples[i] + (2.0*R*cosTheta) * mY1L - (R*R) * mY2L;
		rightSamples[i] = A * rightSamples[i] + (2.0*R*cosTheta) * mY1R - (R*R) * mY2R;

		// Feedback
		mY2L = mY1L;
		mY2R = mY1R;
		mY1L = leftSamples[i];
		mY1R = rightSamples[i];
	}
}
