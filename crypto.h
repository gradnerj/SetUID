/*!
 *    \file  crypto.h
 *   \brief
 *
 *  \author  Jeffrey Gradner, jeffreygradner@mail.weber.edu
 *  *
 *  \internal
 *       Created:  01/14/2020
 *      Revision:  none
 *      Compiler:  gcc
 *     Organization:
 *     Copyright:  Copyright (c) 2020, Jeff Gradner
  */
  #include <stdio.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <string.h>
  
    typedef enum {false, true} bool;

    void Encrypt(void);
    void Decrypt(void);
    void CryptoMenu(void);
