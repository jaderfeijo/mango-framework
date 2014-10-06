<?hh // strict

class Project {

	const string PROJECT_VERSION_FILENAME = 'VERSION';
	const string PROJECT_REVISION_FILENAME = 'REVISION';

	protected string $_path;

	public function __construct(string $path) {
		$this->_path = $path;
	}

	/**************** Properties ****************/

	public function path(): string {
		return $this->_path;
	}

	/*************** Dynamic Properties ***************/

	public function version(): Version {
		$versionString = file_get_contents($this->path().'/'.self::PROJECT_VERSION_FILENAME);
		$revisionString = file_get_contents($this->path().'/'.self::PROJECT_REVISION_FILENAME);
		return Version::parse($versionString.'.'.$revisionString);
	}

}
