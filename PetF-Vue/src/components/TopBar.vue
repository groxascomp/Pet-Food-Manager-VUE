<template>
  <div class="flex justify-between items-center bg-blue-600 text-white px-6 py-2 text-sm">
    <div class="flex gap-4">
      <span>📞 +639 123 6767 420</span>
      <span>✉️ carlyn.vane.diana@gian-pat.com</span>
    </div>
    <div class="flex gap-3">
      <a
        href="https://web.facebook.com/gianexequiel"
        aria-label="Facebook"
        class="hover:text-blue-300 transition"
      >
        <font-awesome-icon :icon="['fab', 'facebook-f']" />
      </a>
      <a
        href="https://www.google.com/search?q=giga+squidward"
        aria-label="Twitter"
        class="hover:text-blue-300 transition"
      >
        <font-awesome-icon :icon="['fab', 'twitter']" />
      </a>
      <a
        href="https://www.linkedin.com/in/exe0107g"
        aria-label="LinkedIn"
        class="hover:text-blue-300 transition"
      >
        <font-awesome-icon :icon="['fab', 'linkedin-in']" />
      </a>
    </div>
  </div>
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
