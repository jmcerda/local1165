<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
global $user;

?>

<header id="page-header">

  <?php if ($logo): ?>
    <div class="logo-wrapper">
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
      <a href="#" id="menu-toggle"><i class="fa fa-bars" aria-hidden="true"></i></a>
    </div>
  <?php endif; ?>

  <div class="navbar grow">

    <div class="top-contacts-wrapper flex-row">
      <div class="top-contacts left-side flex-row">
        <?php if (isset($facebook_url)) : ?>
          <a href="<?php print $facebook_url ?>" class="social topicons"><img src="/<?php print path_to_theme(); ?>/src/img/facebook.png" />Facebook</a>
        <?php endif; ?>
        <?php if (isset($twitter_url)) : ?>
          <a href="<?php print $twitter_url ?>" class="social topicons"><img src="/<?php print path_to_theme(); ?>/src/img/twitter.png" />Twitter</a>
        <?php endif; ?>
      </div>
      <div class="top-contacts right-side flex-row">
        <a class="social topicons instagram" href="<?php print $instagram_url ?>"><img src="/<?php print path_to_theme(); ?>/src/img/instagram.png" />Instagram</a>
        <a class="social topicons" href="/<?php print ($user->uid == 0 ? 'user' : 'user/logout'); ?>"><img src="/<?php print path_to_theme(); ?>/src/img/memberlogin.png" /><?php print ($user->uid == 0 ? 'Member Login' : 'Sign Out'); ?></a>
      </div>
    </div>

    <div class="main-menu-wrapper">
      <?php if ($main_menu): ?>
          <nav class="grow">
            <?php print render($main_menu); ?>
          </nav>
      <?php endif; ?>

    </div>

  </div>
</header>

<?php print render($page['header']); ?>

<?php print $messages; ?>

<?php if ($tabs['#primary'] or $tabs['#secondary']): ?><div class="tabs-wrapper"><?php print render($tabs); ?></div><?php endif; ?>
<?php if ($slider) print render($slider); ?>

<section class="page-content">
  <div class="page-content-inner">
    <?php if ($page['left_sidebar']) : ?>
      <aside id="left-sidebar">
        <?php if ($left_side_image) print render($left_side_image);?>
        <?php print render($page['left_sidebar']); ?>
      </aside>
    <?php endif; ?>
    <div id="content" class="column col-sm-12 col-md-9">
      <div class="section">
        <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
        <?php print render($page['content']); ?>
        <?php print render($page['content_center']); ?>
        <?php print render($page['content_lower']); ?>
      </div>
    </div>
    <?php if ($page['right_sidebar']) : ?>
      <aside id="right-sidebar" class="col-sm-12 col-md-3">
        <?php print render($page['right_sidebar']); ?>
      </aside>
    <?php endif; ?>

  </div>
</section>


<section id="footer">
  <div class="footer-inner">
    <?php if (isset($address)) : ?>
      <div class="footer-address">
        <h4>Contact Us</h4>
        <p><?php print $address ?></p>
      </div>
    <?php endif; ?>
    <div>
      <?php
      $menu_resources_links = menu_navigation_links('menu-resources');
      print theme('links__menu_menu-resources-links', array('links' => $menu_resources_links, 'attributes' => array('class' => array('links', 'clearfix')), 'heading' => t('Resources Links')));
      ?>
    </div>
    <div>
    <?php
    $menu_quick_links = menu_navigation_links('menu-quick-links');
    print theme('links__menu_menu-quick-links', array('links' => $menu_quick_links, 'attributes' => array('class' => array('links', 'clearfix')), 'heading' => t('Quick Links')));
    ?>
    </div>
    <div class="socials">
      <h4>Social Media</h4>
      <?php if (isset($facebook_url)) : ?>
        <a href="<?php print $facebook_url ?>" class="social"><i class="fa fa-facebook" aria-hidden="true"></i></a>
      <?php endif; ?>
      <?php if (isset($twitter_url)) : ?>
        <a href="<?php print $twitter_url ?>" class="social"><i class="fa fa-twitter" aria-hidden="true"></i></a>
      <?php endif; ?>
      <?php if (isset($instagram_url)) : ?>
        <a href="<?php print $instagram_url ?>" class="social"><i class="fa fa-instagram" aria-hidden="true"></i></a>
      <?php endif; ?>
    </div>
  </div>
</section>
<section id="under-footer">
  <div id="copys"><span>Copyright &copy; <?php print date('Y'); ?> </span> <span>Santa Clara County Firefighters,</span> <span>Local 1165</span></div>
  <div id="rights">All rights reserved</div>
</section>

