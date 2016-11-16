(function($) {
  // This jQuery function is called when the document is ready
  $(function() {
     $('form.comment-form').hide();
     $('#comments h2.comment-form').click(function() {
        $('form.comment-form').toggle('slow', function() {
          // Animation complete.
        });
        //add css class to H2 title when clicked//
        $(this).toggleClass("open");
      });
  });
})(jQuery);
