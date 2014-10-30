<?hh

class Package {

	public static function parse(Source $source, string $package) : ?Package {
		$s = new Vector(explode(' ', $package));
		if ($s->count() >= 3) {
			return new Package($source, trim($s[0]), trim($s[1]), trim($s[2]));
		} else {
			return null;
		}
	}
	
	protected Source $_source;
	protected string $_name;
	protected string $_channel;
	protected string $_url;

	public function __construct(Source $source, string $name, string $channel, string $url) {
		$this->_source = $source;
		$this->_name = $name;
		$this->_channel = $channel;
		$this->_url = $url;
	}

	/******************* Properties *******************/

	public function source() : Source {
		return $this->_source;
	}

	public function name() : string {
		return $this->_name;
	}

	public function channel() : string {
		return $this->_channel;
	}

	public function url() : string {
		return $this->_url;
	}

	/**************** Protected Methods *****************/

	protected function packageURL(string $channel) : string {
		return str_replace('{CHANNEL}', $channel, $this->url());
	}

	protected function packagePath(string $channel) : string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$channel.'.zip';
	}

	protected function archivePath(string $channel) : string {
		return $this->source()->cachesPath().'/'.$this->name().'-'.$channel;
	}

	/**************** Methods *****************/

	public function packageURLForVersion(?Version $version) : string {
		$channel = $this->channel();
		if ($version != null) {
			$channel = $version->shortVersionString();
		}
		return $this->packageURL($channel);
	}

	public function packagePathForVersion(?Version $version) : string {
		$channel = $this->channel();
		if ($version != null) {
			$channel = $version->shortVersionString();
		}
		return $this->packagePath($channel);
	}

	public function archivePathForVersion(?Version $version) : string {
		$channel = $this->channel();
		if ($version != null) {
			$channel = $version->shortVersionString();
		}
		return $this->archivePath($channel);
	}

	public function hasPackageForVersion(?Version $version) : bool {
		return file_exists($this->packagePathForVersion($version));
	}

	public function hasArchiveForVersion(?Version $version) : bool {
		return file_exists($this->archivePathForVersion($version));
	}

	public function fetch(?Version $version) : void {
		if (!$this->hasPackageForVersion($version)) {
			FileManager::downloadFile($this->packageURLForVersion($version), $this->packagePathForVersion($version));
		}
	}

	public function extract(?Version $version) : void {
		if (!$this->hasArchiveForVersion($version)) {
			FileManager::extractPackage($this->packagePathForVersion($version), $this->source()->cachesPath());
		}
	}

	public function archiveForVersion(?Version $version) : Archive {
		return new Archive($this->name(), $this->archivePathForVersion($version));
	}
	
}

