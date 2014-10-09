<?hh // strict
	
class Version {

	public static function parse(string $versionString): Version {
		$version = explode('.', $versionString);
		return new Version((int)@$version[0], (int)@$version[1], (int)@$version[2]);
	}

	public static function parseFromFilesInPath(string $path): Version {
		$VERSION = file_get_contents($path.'/VERSION');
		$REVISION = file_get_contents($path.'/REVISION');
		return self::parse("$VERSION.$REVISION");
	}

	private int $_major;
	private int $_minor;
	private int $_revision;
	
	public function __construct(int $major = 0, int $minor = 0, int $revision = 0) {
		$this->_major = $major;
		$this->_minor = $minor;
		$this->_revision = $revision;
	}
	
	public function major(): int {
		return $this->_major;
	}
	
	public function minor(): int {
		return $this->_minor;
	}
	
	public function revision(): int {
		return $this->_revision;
	}
	
	public function isEqualTo(Version $version): bool {
		return ($this->major() == $version->major() && $this->minor() == $version->minor() && $this->revision() == $version->revision());
	}
	
	public function isGreaterThan(Version $version): bool {
		if ($this->major() > $version->major()) {
			return true;
		} else if ($this->major() < $version->major()) {
			return false;
		} else {
			if ($this->minor() > $version->minor()) {
				return true;
			} else if ($this->minor() < $version->minor()) {
				return false;
			} else {
				if ($this->revision() > $version->revision()) {
					return true;
				} else {
					return false;
				}
			}
		}
	}
	
	public function isSmallerThan(Version $version): bool {
		if ($this->major() < $version->major()) {
			return true;
		} else if ($this->major() > $version->major()) {
			return false;
		} else {
			if ($this->minor() < $version->minor()) {
				return true;
			} else if ($this->minor() > $version->minor()) {
				return false;
			} else {
				if ($this->revision() < $version->revision()) {
					return true;
				} else {
					return false;
				}
			}
		}
	}
	
	public function isGreaterThanOrEqualTo(Version $version): bool {
		return ($this->isGreaterThan($version) || $this->isEqualTo($version));
	}
	
	public function isSmallerThanOrEqualTo(Version $version): bool {
		return ($this->isSmallerThan($version) || $this->isEqualTo($version));
	}
	
	public function __toString(): string {
		return $this->major().'.'.$this->minor().'.'.$this->revision();
	}

}
