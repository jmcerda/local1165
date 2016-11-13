(function ($) {
    Drupal.behaviors.customTheme = {
        attach: function (context, settings) {

            var $slider = $('.field-name-field-page-slider');

            if ($slider.find('> .field-items > .field-item').length > 1) {

                $slider.addClass('swiper-container');
                $slider.find('> .field-items').addClass('swiper-wrapper').find('> .field-item').addClass('swiper-slide');

                $slider.append('<div class="swiper-pagination"></div>');
                $slider.append('<div class="swiper-button-prev banner-angle"></div><div class="swiper-button-next banner-angle"></div>');

                var mySwiper = new Swiper ('.swiper-container', {
                    loop: true,
                    pagination: '.swiper-pagination',
                    nextButton: '.swiper-button-next',
                    prevButton: '.swiper-button-prev',
                    paginationClickable: true
                });
            }

            var toggleMenuHandler = function(e) {
                e.preventDefault();
                //$('.navbar').stop().slideToggle(200);
                $('body').toggleClass('menu-opened');
            };

            $('#menu-toggle').click(toggleMenuHandler);

            // Menu
            var $menu = $('.main-menu-wrapper nav > .menu');
            $menu.find('li:eq('+Math.floor($('.main-menu-wrapper nav > .menu > li').length/2)+')').addClass('half-element');

            $(window).resize( function() {
                var windowWidth = $(this).width();
                var imageWidth = $('.field-name-field-slide-image img').first().width() || 1920;
                var diff = Math.ceil((imageWidth - windowWidth)/2);

                $('.field-name-field-slide-image img').css({marginLeft: -diff});
            }).resize();

            $('.field-collection-item-field-people').each( function() {
              var self = this;
              if ($(self).find('.field-name-field-people-description-full .field-item').html().indexOf($(self).find('.field-name-field-people-description .field-item').html()) == -1) {
                $(self).find('.field-name-field-people-description-full').hide();
                $(self).find('.field-name-field-people-description-full .field-item').append('<a style="font-size: 16px;" href="#" class="collapse">collapse</a>');
                $(self).find('.field-name-field-people-description-full .collapse').click(function () {
                  $(self).find('.field-name-field-people-description-full').hide();
                  $(self).find('.field-name-field-people-description').show();
                  return false;
                });
                $(self).find('.field-name-field-people-description .field-item').append('<a style="font-size: 16px;" href="#" class="expand">more&nbsp;info</a>');
                $(self).find('.field-name-field-people-description .expand').click(function () {
                  console.log('work');
                  $(self).find('.field-name-field-people-description-full').show();
                  $(self).find('.field-name-field-people-description').hide();
                  return false;
                });
              } else {
                $(self).find('.field-name-field-people-description').hide();
              }
            });

          $('.view-people .view-content table td').each( function() {
            if ($(this).html().trim() == '') {
              $(this).addClass('empty');
            }
          });

          $('.view-shifts-calendar .calendar-tid').each( function() {
            $(this).closest('.view-item').hide();
          });

          $('.view-shifts-calendar .mini-day-on a').each( function() {
            var color = $(this).attr('background-color');
            $(this).css('color', color);
          });

          $('.view-shifts-calendar .month.day a').each( function() {
            var color = $(this).attr('background-color');
            $(this).css('color', color);
          });

          $('.paragraphs-items-field-page-slider .field-items .swiper-slide').each(function() {
            $(this).find('.field-name-field-slide-button').hide();
            var linkText = $(this).find('.field-name-field-slide-button .field-item a').text().replace(' ', '&nbsp;');
            $(this).find('.field-name-field-slide-button .field-item a').html('(' + linkText + ')');
            var linkHtml = $(this).find('.field-name-field-slide-button .field-item').html();
            if (linkHtml != undefined) {
              var textHtml = $(this).find('.field-name-field-slide-text .field-item').html();
              $(this).find('.field-name-field-slide-text .field-item').html(textHtml + '&nbsp;' + linkHtml);
              $(this).find('.field-name-field-slide-text .field-item a').css('color', '#FFF');
            }
          })

        }
    };
})(jQuery);
