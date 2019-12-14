/*
* Copyright (C) 2019 MadStrawberry
* Distributed under the GNU GPL v2. For full terms see the file LICENSE
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#ifndef _HDC_COM_PTR_H_
#define _HDC_COM_PTR_H_

#if !defined(__cplusplus) 

#define HDC_COM_PTR_RELEASE(object) \
if (object) { (object)->lpVtbl->Release(object); (object) = NULL; }

#define HDC_COM_OBJECT(object) (object)->lpVtbl

#endif

#endif

