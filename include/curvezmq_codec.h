/*  =========================================================================
    curvezmq_codec - core engine (rfc.zeromq.org/spec:26)

    -------------------------------------------------------------------------
    Copyright (c) 1991-2013 iMatix Corporation <www.imatix.com>
    Copyright other contributors as noted in the AUTHORS file.

    This file is part of the CurveZMQ authentication and encryption library.

    This is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the 
    Free Software Foundation; either version 3 of the License, or (at your 
    option) any later version.

    This software is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABIL-
    ITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General 
    Public License for more details.

    You should have received a copy of the GNU Lesser General Public License 
    along with this program. If not, see <http://www.gnu.org/licenses/>.
    =========================================================================
*/

#ifndef __CURVEZMQ_CODEC_H_INCLUDED__
#define __CURVEZMQ_CODEC_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _curvezmq_codec_t curvezmq_codec_t;

//  @interface
//  Constructor
//  Create a new curvezmq_codec instance; if you provide a server-key, is a 
//  client that can talk to that specific server. Otherwise is a server that 
//  will talk to one specific client.
CZMQ_EXPORT curvezmq_codec_t *
    curvezmq_codec_new (byte *server_key);
    
//  Destructor
CZMQ_EXPORT void
    curvezmq_codec_destroy (curvezmq_codec_t **self_p);

//  Set long term keys for this codec; takes ownership of keypair and
//  destroys when destroying the codec.
CZMQ_EXPORT void
    curvezmq_codec_set_keypair (curvezmq_codec_t *self, curvezmq_keypair_t *keypair);

//  Set a metadata property; these are sent to the peer after the
//  security handshake. Property values are strings.
CZMQ_EXPORT void
    curvezmq_codec_set_metadata (curvezmq_codec_t *self, char *name, char *value);

//  Set tracing on curvezmq_codec instance. Will report activity to stdout.
CZMQ_EXPORT void
    curvezmq_codec_set_verbose (curvezmq_codec_t *self, bool verbose);

//  Accept input command from peer. If the command is invalid, it is
//  discarded silently. May return a blob to send to the peer, or NULL
//  if there is nothing to send.
CZMQ_EXPORT zframe_t *
    curvezmq_codec_execute (curvezmq_codec_t *self, zframe_t *input);

//  Encode clear-text message to peer. Returns a blob ready to send
//  on the wire. Encodes frame 'more' property.
CZMQ_EXPORT zframe_t *
    curvezmq_codec_encode (curvezmq_codec_t *self, zframe_t **cleartext_p);

//  Decode blob into message from peer. Takes ownership of encrypted frame.
//  Sets frame 'more' property for application use.
CZMQ_EXPORT zframe_t *
    curvezmq_codec_decode (curvezmq_codec_t *self, zframe_t **encrypted_p);

//  Indicate whether handshake is still in progress
CZMQ_EXPORT bool
    curvezmq_codec_connected (curvezmq_codec_t *self);

//  Self test of this class
void
    curvezmq_codec_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
