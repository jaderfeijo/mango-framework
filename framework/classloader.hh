<?hh

/*
 * Copyright (c) 2011 Movinpixel Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the company nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MOVINPIXEL AND ITS CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL MOVINPIXEL OR ITS CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 * This file is responsible for the auto loading of classes and libraries
 *
 * @author Jader Feijo <jader@movinpixel.com>
 *
 * @license MIT
 */

require_once('constants.hh');
require_once('LibraryManager.hh');

spl_autoload_register('m_auto_load_class');

/**
 * Loads a library into the project
 *
 * This function tells the system where to find library classes
 * of a given version.
 *
 * If you try to specify a library with a given name with a
 * different version more than once it will throw an exception.
 *
 * If no version is specified, the default 'latest' is used
 *
 * If the library and version specified cannot be found this
 * function throws an exception.
 *
 * @example library('myCoolLibrary', '1.0');
 * @example library('com.imagelib.ImageLib', 'latest');
 * @example library('com.imagelib.ImageLib');
 *
 * @param string $name The name of the library to be imported
 * @param string $version The version of the library to be
 * imported
 *
 * @return void
 */
function library(string $library, string $version = MANGO_LIBRARY_DEFAULT_VERSION) : void {
	if (LibraryManager::sharedManager()->addLibrary($library, $version)) {
		$libraryFile = LibraryManager::sharedManager()->pathForLibrary($library).MANGO_LIBRARY_FILENAME;
		if (file_exists($libraryFile)) {
			include($libraryFile);
		}
	}
}

/**
 * This function is called every time a class is first encountered and is
 * responsible for finding the class within the lodaded libraries and
 * including it so it can be used.
 *
 * @param string $class The class to be loaded
 *
 * @return void
 */
function m_auto_load_class(string $class) : void {
	$classPath = LibraryManager::sharedManager()->pathForClass($class);
	if ($classPath !== null) {
		include($classPath);
	}
}

