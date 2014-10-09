<?hh // strict

class Package {

	protected string $_name;
	protected string $_channel;
	protected string $_sourceURL;

	public function __construct(string $name, string $channel, string $sourceURL) {
		$this->_name = $name;
		$this->_channel = $channel;
		$this->_sourceURL = $sourceURL;
	}

	/******************* Properties *******************/

	public function name(): string {
		return $this->_name;
	}

	public function channel(): string {
		return $this->_channel;
	}

	public function sourceURL(): string {
		return $this->_sourceURL;
	}

	/***************** Dynamic Properties ***************/

	public function archiveURL(): string {
		return str_replace('{CHANNEL}', $this->channel(), $this->sourceURL());
	}

	public function isInstalled(): bool {
		return false;
	}

	/***************** Methods ****************/

	public function install(): void {
		//
	}

	public function update(): void {
		//
	}

	public function uninstall(): void {
		//
	}

}

