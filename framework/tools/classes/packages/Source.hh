<?hh // strict

class Source {
	
	public static function parse(string $source) : ?Source {
		$s = explode(' ', $source);
		if (count($s) >= 2) {
			return new Source($s[0], $s[1]);
		} else {
			return null;
		}
	}

	protected string $_name;
	protected string $_url;

	protected Vector<Package> $_packages;

	public function __construct(string $name, string $url) {
		$this->_name = $name;
		$this->_url = $url;

		$this->_packages = new Vector(null);
	}

	/****************** Properties *****************/

	public function name() : string {
		return $this->_name;
	}

	public function url() : string {
		return $this->_url;
	}

	/****************** Dynamic Properties ********************/

	public function cachesPath() : string {
		return PackageManager::sharedManager()->cachesPath().'/sources/'.$this->name();
	}

	public function packagesPath() : string {
		return $this->cachesPath().'/PACKAGES';
	}

	public function isCached() : bool {
		return file_exists($this->packagesPath());
	}

	public function packages() : Vector<Package> {
		if ($this->_packages->isEmpty()) {
			if ($this->isCached()) {
				$this->_packages->clear();
				$file = new File($this->packagesPath(), File::READ_MODE);
				while (!$file->eof()) {
					$line = $file->readLine();
					if ($line !== null) {
						$package = Package::parse($this, $line);
						if ($package !== null) {
							$this->_packages->add($package);
						}
					}	
				}
				$file->close();
			}
		}
		return $this->_packages;
	}

	/****************** Methods *******************/

	public function fetch() : void {
		if (!$this->isCached()) {
			FileManager::downloadFile($this->url(), $this->packagesPath());
			$this->packages()->clear();
		}
	}

	public function clearCache() : void {
		if ($this->isCached()) {
			FileManager::removeFile($this->packagesPath());
			$this->packages()->clear();
		}
	}

	public function packageNamed(string $name) : ?Package {
		foreach ($this->packages() as $package) {
			if ($package->name() == $name) {
				return $package;
			}
		}
		return null;
	}

}
