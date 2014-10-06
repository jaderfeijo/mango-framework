<?hh // decl

define('AL_CLASSES_FOLDER', 'classes');
define('AL_CLASS_EXTENSION', 'hh');

spl_autoload_register('al_auto_load_class');

function al_auto_load_class(string $class): void {
	$classPath = find_class_path($class);
	if ($classPath !== null) {
		include $classPath;
	}
}

function find_class_path(string $className, ?string $path = null): ?string {
	if ($path === null) $path = dirname(__FILE__).'/'.AL_CLASSES_FOLDER;

	$dir = new DirectoryIterator($path);
	foreach ($dir as $fileInfo) {
		if (!$fileInfo->isDot()) {	
			if ($fileInfo->isDir()) {
				$path = find_class_path($className, $fileInfo->getPathname());
				if ($path !== null) {
					return $path;
				}
			} else {
				if ($fileInfo->getExtension() == AL_CLASS_EXTENSION) {
					$fileName = str_replace('.'.AL_CLASS_EXTENSION, '', $fileInfo->getFilename());
					if ($fileName == $className) {
						return $fileInfo->getPathname();
					}
				}
			}
		}
	}

	return null;
}

