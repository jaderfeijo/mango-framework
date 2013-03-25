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
	
	import('mango.system.*');
	
	/**
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @package mango.system
	 *
	 */
	class MApplicationController extends MObject {
		
		protected $controllerClassName;
		protected $name;
		protected $parameters;
		protected $acceptedMethods;
		
		public function __construct(MString $controllerClassName, MString $name = null) {
			parent::__construct();
			
			$this->controllerClassName = $controllerClassName;
			$this->name = ($name ? $name : S(""));
			$this->parameters = new MMutableArray();
			$this->acceptedMethods = new MMutableArray();
		}
		
		/******************** Properties ********************/
		
		/**
		 * @return MString
		 */
		public function controllerClassName() {
			return $this->controllerClassName;
		}
		
		/**
		 * @return MString
		 */
		public function name() {
			return $this->name;
		}
		
		/**
		 * @return MArray
		 */
		public function parameters() {
			return $this->parameters;
		}
		
		/**
		 * @return MArray
		 */
		public function requiredParameters() {
			$requiredParameters = new MMutableArray();
			foreach ($this->parameters()->toArray() as $parameter) {
				if ($parameter->required()) {
					$requiredParameters->addObject($parameter);
				}
			}
			return $requiredParameters;
		}
		
		/**
		 * @return MArray
		 */
		public function acceptedMethods() {
			return $this->acceptedMethods;
		}
		
		/******************** Methods ********************/
		
		/**
		 * @return void
		 */
		public function addParameter(MApplicationControllerParameter $parameter) {
			$this->parameters->addObject($parameter);
		}
		
		/**
		 * @return void
		 */
		public function removeParameter(MApplicationControllerParameter $parameter) {
			$this->parameters->removeObject($parameter);
		}
		
		/**
		 * @return void
		 */
		public function removeAllParameters() {
			$this->parameters->removeAllObjects();
		}
		
		/**
		 * @return MApplicationControllerParameter
		 */
		public function parameterWithName(MString $name) {
			foreach ($this->parameters()->toArray() as $parameter) {
				if ($parameter->name()->equals($name)) {
					return $parameter;
				}
			}
			return null;
		}
		
		/**
		 * @return void
		 */
		public function addAcceptedMethod(MApplicationControllerAcceptedMethod $method) {
			$this->acceptedMethods->addObject($method);
		}
		
		/**
		 * @return void
		 */
		public function removeAcceptedMethod(MApplicationControllerAcceptedMethod $method) {
			$this->acceptedMethods->removeObject($method);
		}
		
		/**
		 * @return void
		 */
		public function removeAllAcceptedMethods() {
			$this->acceptedMethods->removeAllObjects();
		}
		
		/**
		 * @return bool
		 */
		public function acceptsMethod(MString $method) {
			foreach ($this->acceptedMethods()->toArray() as $acceptedMethod) {
				if ($acceptedMethod->method()->equals($method)) {
					return true;
				}
			}
			return false;
		}
		
		/**
		 * @return MApplicationControllerAcceptedMethod
		 */
		public function acceptedMethodForMethod(MString $method) {
			foreach ($this->acceptedMethods()->toArray() as $acceptedMethod) {
				if ($acceptedMethod->method()->equals($method)) {
					return $acceptedMethod;
				}
			}
			return null;
		}
		
	}

?>