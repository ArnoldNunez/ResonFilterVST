/**
 * \file ResonFilter.h
 *
 * \author Arnold N
 *
 * \brief The reson filter
 */
#pragma once

/**
 * The reson filter component. This filter emphasizes one
 * specific frequency range. The frequency to emphasize is
 * a normalized frequncy with a bandwidth to determine how
 * selective the filter is. The equation for a reson is as follows:
 *
 *	R = 1 - B/2
 *	cos É∆ = (2Rcos (2ÉŒf)) / (1 + R^2)
 *	A = (1 - R^2) sin É∆
 *	yt = Ax_t + (2Rcos É∆)yt-1 - (R^2)(y_t-2)
 *
 * Where f is the resonant frequency. cos É∆ is the cosine of the
 * pole angle. B is the bandwidth (range of (0, 1]).
 */
class CResonFilter
{
public:
	/** Default constructor */
	CResonFilter();
	/** Copy constructor (disabled) */
	CResonFilter(const CResonFilter&) = delete;
	/** Default destructor */
	virtual ~CResonFilter();

	/** Reson filter processor
	* The audio samples in the specified frequency range
	* are enhanced.
	*
	* \param leftSamples Ptr to left channel audio buffer
	* \param rightSamples Ptr to right channel audio buffer
	* \param numSamples the number of samples in the buffer
	*/
	void BlockProcess(float* leftSamples, float* rightSamples, int numSamples);


	void ClockProcess(float* leftSample, float* rightSample) {}

private:

	float mFreq;		///< The normalized resonant frequency (Hz)
	float mBand;		///< The bandwidth of the filter
	float mGain;		///< Gain of the filter

	double mY1L = 0;		/// One output sample in the past
	double mY2L = 0;		/// Two outputs samples in the past
	double mY1R = 0;
	double mY2R = 0;
};

