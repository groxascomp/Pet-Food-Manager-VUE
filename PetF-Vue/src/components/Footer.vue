<template>
  <footer class="bg-gray-800 text-gray-300 py-6">
    <div
      class="w-full px-0 footer__inner flex flex-col md:flex-row justify-between items-center md:items-start gap-4"
    >
      <!-- Far left: contact info -->
      <div
        class="flex flex-col text-sm md:order-1 md:text-left w-full md:w-auto"
        style="padding-left: 50px;"
      >
        <span>📞 +639 123 6767 420</span>
        <span>✉️ carlyn.vane.diana@gian-pat.com</span>
      </div>

      <!-- Center: copyright -->
      <div class="text-center md:order-2 w-full md:w-auto">
        <p>© {{ new Date().getFullYear() }} PetF. All rights reserved.</p>
      </div>

      <!-- Far right: social icons -->
      <div
        class="flex gap-3 text-white md:order-3 md:justify-end w-full md:w-auto"
        style="padding-right: 50px; padding-left: 142px;"
      >
        <a
          href="https://web.facebook.com/gianexequiel"
          aria-label="Facebook"
          class="hover:text-blue-400 transition"
        >
          <font-awesome-icon :icon="['fab', 'facebook-f']" />
        </a>
        <a
          href="https://www.google.com/search?q=giga+squidward"
          aria-label="Twitter"
          class="hover:text-blue-400 transition"
        >
          <font-awesome-icon :icon="['fab', 'twitter']" />
        </a>
        <a
          href="https://www.linkedin.com/in/exe0107g"
          aria-label="LinkedIn"
          class="hover:text-blue-400 transition"
        >
          <font-awesome-icon :icon="['fab', 'linkedin-in']" />
        </a>
      </div>
    </div>
  </footer>
</template>

<script setup>
// Import Font Awesome Vue
import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome'
import { library } from '@fortawesome/fontawesome-svg-core'
import { faFacebookF, faTwitter, faLinkedinIn } from '@fortawesome/free-brands-svg-icons'

library.add(faFacebookF, faTwitter, faLinkedinIn)
</script>

<style scoped>
/* Scoped styles if needed, otherwise rely on Tailwind/App.css */
</style>
