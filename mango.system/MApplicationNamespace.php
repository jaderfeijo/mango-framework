<?php

	/*
	 * Copyright (c) 2011 Movinpixel Ltd. All rights reserved.
	 *
	 * Redistribution and use in source and binary forms, with or without
	 * modification, are permitted provided that the following conditions
	 * are met:
	 * 1. Redistributions of source code must retain the above copyright
	 *    notice, this list of conditions and the following disclaimer.
	 * 2. Redistributions in binary form must reproduce the above copyright
	 *    notice, this list of conditions and the following disclaimer in the
	 *    documentation and/or other materials provided with the distribution.
	 * 3. Neither the name of the company nor the names of its contributors
	 *    may be used to endorse or promote products derived from this software
	 *    without specific prior written permission.
	 *
	 * THIS SOFTWARE IS PROVIDED BY MOVINPIXEL AND ITS CONTRIBUTORS ``AS IS'' AND
	 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	 * ARE DISCLAIMED.  IN NO EVENT SHALL MOVINPIXEL OR ITS CONTRIBUTORS BE LIABLE
	 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
	 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
	 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
	 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
	 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	 * SUCH DAMAGE.
	 */
	
	package('mango.system');
	
	import('mango.system.exceptions.*');
	
	/**
	 * 
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @license MIT
	 *
	 * @package mango.system
	 *
	 */
	class MApplicationNamespace extends MObject {
		
		//
		// ************************************************************
		//
		
		protected $name;
		protected $parentNamespace;
		protected $childNamespaces;
		protected $viewControllers;
		protected $mainViewController;
		protected $errorViewControllerClass;
		
		/**
		 * 
		 *
		 * @return MApplicationNamespace
		 */
		public function __construct(MString $name = null, MApplicationNamespace $parentNamespace = null) {
			parent::__construct();
			
			$this->name = ($name ? $name : S(""));
			$this->parentNamespace = $parentNamespace;
			$this->childNamespaces = new MMutableArray();
			$this->viewControllers = new MMutableArray();
			$this->mainViewController = null;
			$this->errorViewControllerClass = null;
		}
		
		/******************** Properties ********************/
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function name() {
			return $this->name;
		}
		
		/**
		 * @return MApplicationNamespace
		 */
		public function parentNamespace() {
			return $this->parentNamespace;
		}
		
		/**
		 * 
		 *
		 * @return MArray
		 */
		public function childNamespaces() {
			return $this->childNamespaces;
		}
		
		/**
		 * 
		 *
		 * @return MArray
		 */
		public function viewControllers() {
			return $this->viewControllers;
		}
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function setMainViewController(MApplicationController $mainViewController) {
			$this->mainViewController = $mainViewController;
		}
		
		/**
		 * 
		 *
		 * @return MApplicationController
		 */
		public function mainViewController() {
			return $this->mainViewController;
		}
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function setErrorViewControllerClass(MString $errorViewControllerClass = null) {
			$this->errorViewControllerClass = $errorViewControllerClass;
		}
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function errorViewControllerClass() {
			if ($this->errorViewControllerClass) {
				return $this->errorViewControllerClass;
			} else if ($this->parentNamespace() != null) {
				return $this->parentNamespace()->errorViewControllerClass();
			} else {
				return S("mango.system.MErrorViewController");
			}
		}
		
		/******************** Methods ********************/
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function addChildNamespace(MApplicationNamespace $namespace) {
			if (!$namespace->name()->isEmpty()) {
				$this->childNamespaces->addObject($namespace);
			} else {
				throw new MInvalidOperationException(S("Cannot add a child namespace with no name"));
			}
		}
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function removeChildNamespace(MApplicationNamespace $namespace) {
			$this->childNamespaces->removeObject($namespace);
		}
		
		/**
		 *
		 * @return MApplicationNamespace
		 */
		public function childNamespaceWithName(MString $name) {
			foreach ($this->childNamespaces()->toArray() as $namespace) {
				if ($namespace->name()->equals($name)) {
					return $namespace;
				}
			}
			return null;
		}
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function addViewController(MApplicationController $controller) {
			$this->viewControllers->addObject($controller);
		}
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function removeViewController(MApplicationController $controller) {
			$this->viewControllers->removeObject($controller);
		}
		
		/**
		 * 
		 *
		 * @return MApplicationController
		 */
		public function viewControllerForName(MString $name) {
			foreach ($this->viewControllers()->toArray() as $controller) {
				if ($controller->name()->equals($name)) {
					return $controller;
				}
			}
			return null;
		}
		
		/**
		 * 
		 *
		 * @return MViewController
		 */
		public function viewControllerForPath(MArray $path) {
			$controller = null;
			
			if ($path->count() > 0) {
				$name = $path->objectAtIndex(0);
				$controller = $this->viewControllerForName($name);
				if (!$controller) {
					$namespace = $this->childNamespaceWithName($name);
					if ($namespace) {
						return $namespace->viewControllerForPath($path->subarrayFromIndex(1));
					}
				}
			} else {
				$controller = $this->mainViewController();
			}
			
			$viewController = null;
			
			if ($controller != null) {
				$parameters = $path->subarrayFromIndex(1);
				$reflectionClass = MObject::reflectionClass($controller->controllerClassName());
				$reflectionConstructor = $reflectionClass->getMethod("__construct");
				if ($parameters->count() >= $reflectionConstructor->getNumberOfRequiredParameters()) {
					if ($parameters->count() > 0) {
						$viewController = $reflectionClass->newInstanceArgs($parameters->toArray());
					} else {
						$viewController = $reflectionClass->newInstance();
					}
				} else {
					throw new MBadRequestException();
				}
			} else {
				return MObject::newInstanceOfClassWithParameters($this->errorViewControllerClass(), A(
					MHTTPResponse::RESPONSE_NOT_FOUND, N(MHTTPResponse::RESPONSE_NOT_FOUND), S("Not Found"), S("Sorry but the page you are looking for could not be found")
				));
			}
			
			$viewController->setApplicationController($controller);
			return $viewController;
		}
		
	}

?>