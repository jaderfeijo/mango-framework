<?hh
	
/**
 * This file defines various Mango constants
 * which are used throughout the system.
 */

/**
 * The absolute Mango installation path inside your system
 */
define('MANGO_HOME', '/usr/lib/mango');

/**
 * The name for the Mango library folder inside
 * the Mango installation path
 */
define('MANGO_LIBRARY_FOLDER', 'library');

/**
 * The path where all installed mango libraries reside
 */
define('MANGO_LIBRARY_PATH', MANGO_HOME.'/'.MANGO_LIBRARY_FOLDER);

/**
 * The Mango system library name
 */
define('MANGO_SYSTEM_LIBRARY', 'mangoSystemLib');

/**
 * The Mango class extension
 */
define('MANGO_CLASS_EXTENSION', 'hh');

/**
 * The Mango classes folder
 */
define('MANGO_CLASSES_FOLDER', 'classes');

/**
 * Mango library file name
 */
define('MANGO_LIBRARY_FILENAME', 'library.'.MANGO_CLASS_EXTENSION);

/**
 * Mango library default version
 */
define('MANGO_LIBRARY_DEFAULT_VERSION', 'latest');

