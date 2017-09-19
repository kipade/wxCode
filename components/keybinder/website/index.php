<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<?php
  ////////////////////////////////////////////////////////////////////////////////////////////
  // Author: Francesco Montorsi
  // Creation date: 7/7/2005
  // RCS-ID: $Id: index.php 109 2005-07-09 13:35:34Z frm $
  // Notes: the index page of the website of this component
  ////////////////////////////////////////////////////////////////////////////////////////////
?>

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en-AU">
	<?php       
      $compname = "KeyBinder";
      $subdir = "keybinder";
      require("compwebsite.inc.php");
  ?>

	<br/><?php write_h1("Screenshots"); ?>
	<p>Obviously, since keybinder is not an application, the following screenshots
	refer to the sample application included with this module which shows the usage
	of the keybinder classes.<br/>The following screenshots have been taken on a
	Windows XP system using different build flags:</p>
	
	<div class="center">
	<?php writeScreenshotLink("win1.png", "The keybinder sample running with wxMSW 2.5.3"); ?>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<?php writeScreenshotLink("win2.png", "The keybinder sample running with wxMSW 2.5.3"); ?>
	</div>
	
	<p>The following ones instead have been taken on Red Hat Linux 9.0:</p>

	<div class="center">
	<?php writeScreenshotLink("gtk3.png", "The keybinder sample running with wxGTK 2.5.3"); ?>
	&nbsp;&nbsp;&nbsp;&nbsp;
	<?php writeScreenshotLink("gtk4.png", "The keybinder sample running with wxGTK 2.5.3"); ?>
  </div>


  <br/><?php write_h1("Documentation"); ?>
  <p>The doxygen-generated documentation for this component is available online
  <a href="../../docs/keybinder/">here</a>. Please let me know if you think something is missing.</p>
  

	<br/><?php write_h1("Known bugs"); ?>
  <p>None. To submit a bug report please look at <a href="../../faq.php">wxCode FAQ</a>.</p>

    
	<br/><?php write_h1("Future enhancements"); ?>
  <p>None. To submit a feature request please look at <a href="../../faq.php">wxCode FAQ</a>.</p>
    

	<br/><?php require("footer.inc.php"); ?>
</html>
