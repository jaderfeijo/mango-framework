<?hh // strict

class Source {
	
	public static function parse(string $source) {
		$s = explode(' ', $source);
		return new Source($s[0], $s[1]);
	}

	protected string $_name;
	protected string $_url;

	public function __construct(string $name, string $url) {
		$this->_name = $name;
		$this->_url = $url;
	}

	/****************** Properties *****************/

	public function name(): string {
		return $this->_name;
	}

	public function url(): string {
		return $this->_url;
	}

	/****************** Dynamic Properties ********************/

	public function localPath(): string {
		return PackageManager::sharedManager()->cachesPath().'/sources/'.$this->name();
	}

	public function packagePath(): string {
		return $this->localPath().'/PACKAGES';
	}

	public function isCached(): bool {
		return file_exists($this->packagePath());
	}

	public function packages(): Vector<Package> {
		$packages = new Vector(null);
		
		return Vector { };
	}

	/****************** Methods *******************/

	public function fetch(): void {
		if (!$this->isCached()) {
			
		}
	}

}

