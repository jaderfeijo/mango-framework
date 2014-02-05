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
	 
	package('mango.system.html');
	
	import('mango.system.*');
	
	/**
	 * 
	 *
	 * @author Jader Feijo <jader@movinpixel.com>
	 *
	 * @license MIT
	 *
	 * @package mango.system.html
	 *
	 */
	class MHTMLDocumentView extends MHTMLElementView {
		
		//
		// ************************************************************
		//
		
		protected $headElementView;
		protected $bodyElementView;
		protected $titleElementView;
		
		/**
		 * 
		 *
		 * @return MHTMLDocumentView
		 */
		public function __construct(MString $title = null) {
			parent::__construct(S("html"));
			
			$this->headElementView = new MHTMLElementView(S("head"));
			$this->addSubview($this->headElementView);
			
			$this->bodyElementView = new MHTMLElementView(S("body"));
			$this->addSubview($this->bodyElementView);
			
			$this->titleElementView = new MHTMLElementView(S("title"), $title);
			$this->headElementView->addSubview($this->titleElementView);
		}
		
		/******************** Properties ********************/
		
		/**
		 * @return MHTMLElementView
		 */
		public function headElementView() {
			return $this->headElementView;
		}
	
		/**
		 * @return MHTMLElementView
		 */
		public function bodyElementView() {
			return $this->bodyElementView;
		}
	
		/**
		 * @return MHTMLElementView
		 */
		public function titleElementView() {
			return $this->titleElementView;
		}
		
		/**
		 *
		 *
		 * @return void
		 */
		public function addHeadElement(MHTMLElementView $element) {
			$this->headElementView()->addSubview($element);
		}
		
		/**
		 *
		 *
		 * @return void
		 */
		public function removeHeadElement(MHTMLElementView $element) {
			$this->headElementView()->removeSubview($element);
		}
		
		/**
		 *
		 *
		 * @return MArray
		 */
		public function headElements() {
			return $this->headElementView()->subviews();
		}
		
		/**
		 * @return void
		 */
		public function addBodyElement(MHTMLView $view) {
			$this->bodyElementView()->addSubview($view);
		}
	
		/**
		 * @return void
		 */
		public function removeBodyElement(MHTMLView $view) {
			$this->bodyElementView()->removeSubview($view);
		}
	
		/**
		 * @return MArray
		 */
		public function bodyElements() {
			return $this->bodyElementView()->subviews();
		}
		
		/**
		 * 
		 *
		 * @return void
		 */
		public function setTitle(MString $title) {
			$this->titleElementView()->setText($title);
		}
		
		/**
		 * 
		 *
		 * @return MString
		 */
		public function title() {
			return $this->titleElementView()->text();
		}
		
	}

?>