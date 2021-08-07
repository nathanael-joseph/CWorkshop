/*
-------------------------------------------------------------------------------
Author: Nathanael J Y
Last Modified: 07/08/2021
Written for: The Open University Of Israel
Course: 20465 - C Programming Workshop
Assignment: Maman 14
-------------------------------------------------------------------------------
*/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include "assembler_state.h"
#include "system_utils/error_logging.h"
#include "system_utils/file_management.h"
#include "datastructures/linkedlist_buffer.h"
#include "datastructures/dictionary.h"


/* --- CONSTANTS ------------------------------------------ */

#define COMMENT_CHAR			(';')
#define PIPELINE_ACTION_COUNT 	(4)

/* --- TYPE DEFINITIONS ----------------------------------- */

typedef void (*Action)(); 

/* --- FUNCTION DECLARATIONS ------------------------------ */




#endif
