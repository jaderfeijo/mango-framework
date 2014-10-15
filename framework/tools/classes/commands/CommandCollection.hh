<?hh // strict

class CommandCollection extends Command {
	
	protected Vector<Command> $_commands;
	
	public function __construct(string $name) {
		parent::__construct($name, null, null, null);
		$this->_commands = new Vector(null);
	}
	
	/******************* Properties *******************/
	
	public function commands() : Vector<Command> {
		return $this->_commands;
	}
	
	public function addCommand(Command $command) : void {
		$this->commands()->add($command);
		$command->setParent($this);
	}
	
	public function removeCommand(Command $command) : void {
		$index = $this->commands()->linearSearch($command);
		if ($index >= 0) {
			$this->commands()->removeKey($index);
		}
	}
	
	/******************* Dynamic Properties *******************/
	
	public function executableCommands() : Vector<Command> {
		$commands = new Vector(null);
		foreach ($this->commands() as $command) {
			if (!($command instanceof CommandCollection)) {
				$commands->add($command);
			}
		}
		return $commands;
	}
	
	public function commandCollections() : Vector<CommandCollection> {
		$commands = new Vector(null);
		foreach ($this->commands() as $command) {
			if ($command instanceof CommandCollection) {
				$commands->add($command);
			}
		}
		return $commands;
	}
	
	/******************* Methods *******************/
	
	public function commandWithName(string $name) : ?Command {
		foreach ($this->commands() as $command) {
			if ($command->name() == $name) {
				return $command;
			}
		}
		return null;
	}
	
	/******************* Command Methods *******************/

	public function usageString() : string {
		$usage = $this->fullCommandString().' '.$this->fullArgumentsString()."\n";	
		$commands = $this->commands();
		if ($commands !== null) {
			foreach ($commands as $command) {
				$lines = explode("\n", $command->usageString());
				foreach ($lines as $line) {
					if ($line != '') {
						$usage .= '    '.$line."\n";
					}
				}
				if ($command instanceof CommandCollection) {
					$usage .= "\n";
				}
			}
		}
		return $usage;
	}

	public function run(Vector<string> $args) : int {
		if ($args->count() <= 0) {
			return $this->usage(self::ERR_TOO_FEW_ARGUMENTS);
		} else {
			return $this->execute($args);
		}
	}

	public function execute(Vector<string> $args) : int {
		$command = $this->commandWithName($args[0]);
		if ($command === null) {
			return $this->usage(self::ERR_COMMAND_NOT_FOUND);
		} else {
			return $command->execute(new Vector(array_slice($args->toArray(), 1, $args->count() - 1)));	
		}
	}

}
