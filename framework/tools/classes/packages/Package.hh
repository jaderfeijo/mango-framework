<?hh // strict

class Package {

	public static function parse(Source $source, string $package): ?Package {
		$s = explode(' ', $package);
		if (count($s) >= 3) {
			return new Package($source, $s[0], $s[1], $s[2]);
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

	public function source(): Source {
		return $this->_source;
	}

	public function name(): string {
		return $this->_name;
	}

	public function channel(): string {
		return $this->_channel;
	}

	public function url(): string {
		return $this->_url;
	}

	/***************** Dynamic Properties ***************/

	public function archiveURL(): string {
		return str_replace('{CHANNEL}', $this->channel(), $this->url());
	}

	public function archivePath(): string {
		return $this->source()->cachesPath().'/'.$this->name().'.zip';
	}

	public function path(): string {
		return MangoSystem::system()->libraryHome().'/'.$this->name();
	}

	public function isInstalled(): bool {
		return file_exists($this->path());
	}

	/**************** Methods *****************/

	public function install(): void {
		if (FileManager::downloadFile($this->archiveURL(), $this->archivePath())) {
			
		} else {
			//
		}
	}

	public function uninstall(): void {
		//
	}

}

