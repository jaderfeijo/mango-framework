<?hh

class PackageException extends Exception {

	const int CORRUPTED_PACKAGE_ERROR = 1000;
	const int PACKAGE_NOT_FOUND_ERROR = 1001;
	const int POST_INSTALLATION_ERROR = 1002;

	public function __construct(Package $package, int $reason) {
		$message = "Unknown package error with package named '".$package->name()."'!";
		if ($reason == PackageException::CORRUPTED_PACKAGE_ERROR) {
			$message = "The installation package for the package named '".$package->name()."' was corrupted!";
		} else if ($reason == PackageException::PACKAGE_NOT_FOUND_ERROR) {
			$message = "The installation package for the package named '".$package->name()."' could not be found!";
		} else if ($reason == PackageException::POST_INSTALLATION_ERROR) {
			$message = "A post installation error occurred when installing package named '".$package->name()."'!";
		}
		parent::__construct($message, $reason);
	}

}
