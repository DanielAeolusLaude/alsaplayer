//-------------------------------------------------------------------------
//  This class encapsulates a flac stream.  Only the functions
//  needed by the alsaplayer flac plugin are implemented.
//
//  Copyright (c) 2002 by Drew Hess <dhess@bothan.net>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//-------------------------------------------------------------------------


#ifndef _FLAC_STREAM_H_
#define _FLAC_STREAM_H_

#include <string>
#include "reader.h"

extern "C"
{
#include <FLAC/stream_decoder.h>
}

#undef DEBUG

namespace Flac
{

class FlacEngine;
class FlacTag;

class FlacStream
{
 public:

    //--------------------------------------------------------------
    // Return true if we think name points to  a valid flac stream.
    //--------------------------------------------------------------

    static bool isFlacStream (const std::string & name);

    
 public:

    //--------------------------
    // Constructor & destructor.
    //--------------------------

    FlacStream (const std::string & name, reader_type * f);

    virtual ~FlacStream ();


    //------------------------------------------------------------------
    // Initialize the stream decoder, installing all callbacks from the
    // engine.  Returns false if the decoder could not be initialized.
    //------------------------------------------------------------------

    virtual bool        open ();


    //----------------------------------------------------------
    // Get a pointer to the FlacEngine for this stream decoder.
    //----------------------------------------------------------

    FlacEngine *        engine () const;


    //---------------------------------------------
    // Set the FlacEngine for this stream decoder.
    //---------------------------------------------

    void                setEngine (FlacEngine * engine);


    //----------------------------------------------------------------------
    // Get a pointer to the FlacTag for this stream, or 0 if there is none.
    //----------------------------------------------------------------------

    FlacTag *           tag () const;


    //----------------------------------
    // Set the FlacTag for this stream.
    //----------------------------------

    void                setTag (FlacTag * tag);


    //-----------------------------------
    // Get the name of the flac stream.
    //-----------------------------------

    const std::string & name () const;


    //------------------------------------------------------
    // Get the sample rate of the uncompressed audio stream.
    //------------------------------------------------------

    unsigned int                sampleRate () const;


    //----------------------------------------
    // Number of channels in the audio stream.
    //----------------------------------------

    unsigned int                channels () const;


    //----------------------------------------------------------
    // Total number of uncompressed samples in the audio stream.
    //----------------------------------------------------------

    FLAC__uint64                totalSamples () const;


    //--------------------------------------------------------------
    // The number of uncompressd samples in one block of audio data.
    //--------------------------------------------------------------

    unsigned int                samplesPerBlock () const;


    //-----------------
    // Bits per sample.
    //-----------------

    unsigned int                bps () const;


    //----------------------------------------------------------------
    // Process the next flac frame in the stream.  This has the side-
    // effect of calling the write callback if there is data to fetch
    // in the stream.
    //
    // Returns false if there's no more data in the stream, or if
    // there's an error in the stream decoder.
    //----------------------------------------------------------------

    virtual bool                processOneFrame ();


    //-------------------------------------------------------------------
    // Seeks are unsupported.  Returns false.
    //-------------------------------------------------------------------

    virtual bool                seekAbsolute (FLAC__uint64);


 protected:

    FlacStream ();


 protected:

    FlacEngine *  _engine;
    bool          _mcbSuccess;
    reader_type * _datasource;

    //---------------------------------------------------------------------
    // Stream info.  "Samples" always refers to uncompressed audio samples.
    //---------------------------------------------------------------------

    unsigned int  _channels;      // number of channels in the stream
    unsigned int  _bps;           // bits per sample
    unsigned int  _sampleRate;    // number of samples per channel per sec
    unsigned int  _sampPerBlock;  // number of samples per block of data
    FLAC__uint64  _totalSamp;     // total number of samples in the stream

    
 private:

    //-----------------------------------------------------------------
    // The flac metadata callback.  It's called as a side effect of the
    // open method.  It'll be called once for each metadata block in
    // the flac stream.  To check its success, look at _mcbSuccess.
    //-----------------------------------------------------------------

    static void metaCallBack (const FLAC__StreamDecoder * decoder,
			      const FLAC__StreamMetadata * md,
			      void * cilent_data);

    static FLAC__StreamDecoderWriteStatus 
	writeCallBack (const FLAC__StreamDecoder * decoder,
		       const FLAC__Frame * frame,
		       const FLAC__int32 * const buffer[],
		       void * client_data);

    static FLAC__StreamDecoderReadStatus
	readCallBack (const FLAC__StreamDecoder * decoder,
		      FLAC__byte buffer[],
		      unsigned * bytes,
		      void * client_data);

    static void errCallBack (const FLAC__StreamDecoder * decoder,
			     FLAC__StreamDecoderErrorStatus status,
			     void * client_data);


 private:

    FLAC__StreamDecoder * _decoder;
    FlacTag *             _tag;
    const std::string     _name;


}; // class FlacStream


//----------------
// Inline methods.
//----------------

inline FlacTag *
FlacStream::tag () const
{
    return _tag;
}

inline FlacEngine *
FlacStream::engine () const
{
    return _engine;
}

inline void
FlacStream::setEngine (FlacEngine * engine)
{
    _engine = engine;
}

inline void
FlacStream::setTag (FlacTag * tag)
{
    _tag = tag;
}

inline const std::string &
FlacStream::name () const
{
    return _name;
}

inline unsigned int
FlacStream::sampleRate () const
{
    return _sampleRate;
}

inline FLAC__uint64
FlacStream::totalSamples () const
{
    return _totalSamp;
}

inline unsigned int
FlacStream::samplesPerBlock () const
{
    return _sampPerBlock;
}

inline unsigned int
FlacStream::bps () const
{
    return _bps;
}

inline unsigned int
FlacStream::channels () const
{
    return _channels;
}

inline bool
FlacStream::seekAbsolute (FLAC__uint64 sample)
{
    return false;
}

} // namespace Flac

#endif // _FLAC_STREAM_H_
