<template>
  <NavBar />
  <section
    id="home"
    class="hero h-[684px]"
    style="
      background: linear-gradient(-90deg, rgba(81, 104, 124, 0), rgba(56, 73, 111, 0)),
                 url('/cat-food-bg.jpg') center center / cover no-repeat fixed;
      padding-bottom: 23px;
    "
  >
    <div
      class="hero__content container h-[322px]"
      style="padding-top: 37px; padding-left: 45px;"
    >
      <h1 class="hero__title text-6xl font-extrabold text-gray-800">
        PetF.
      </h1>

      <div class="hero__login flex flex-col gap-4 mt-6 max-w-sm">
        <input
          type="text"
          placeholder="Username"
          v-model="username"
          class="bg-[rgb(189,222,238)] border border-[#111827] rounded px-3 py-2 focus:outline-none focus:ring-2 focus:ring-[rgb(13,58,81)] placeholder-[#111827]"
        />
        <input
          type="password"
          placeholder="Password"
          v-model="password"
          class="bg-[rgb(189,222,238)] border border-[#111827] rounded px-3 py-2 focus:outline-none focus:ring-2 focus:ring-[rgb(13,58,81)] placeholder-[#111827]"
        />
        <button
          @click="handleLogin"
          class="bg-[rgb(13,58,81)] hover:bg-[rgb(83,126,149)] text-white font-bold py-2 px-4 rounded shadow"
        >
          Log In
        </button>
        <p v-if="error" class="text-red-600 text-sm">{{ error }}</p>
      </div>

      <!-- ✅ Hidden audio element for bonk sound -->
      <audio ref="audioRef">
        <source src="/bonk.mp3" type="audio/mpeg" />
      </audio>
    </div>
  </section>
  <Footer />
</template>

<script setup>
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import NavBar from '../components/NavBarlogin.vue'
import Footer from '../components/Footer.vue'

const router = useRouter()
const username = ref('')
const password = ref('')
const error = ref('')
const audioRef = ref(null)

const handleLogin = () => {
  if (username.value === 'ESP' && password.value === '676767') {
    router.push('/login-anim')
  } else {
    error.value = 'Invalid username or password'
    if (audioRef.value) {
      audioRef.value.play().catch(err => console.error('Audio play failed:', err))
    }
  }
}
</script>

<style scoped>
/* Scoped styles if needed, otherwise rely on Tailwind/App.css */
</style>
