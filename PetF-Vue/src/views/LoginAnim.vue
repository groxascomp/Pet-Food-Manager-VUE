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
      class="hero__content container h-[322px] flex flex-col items-center justify-center"
      style="padding-top: 37px; padding-left: 45px;"
    >
    
      <div class="flex items-center justify-center gap-4">
        <h1 class="hero__title text-6xl font-extrabold text-gray-800">
          Welcome 🎉
        </h1>
        <img
          v-if="showGif"
          src="/oiia-cat.gif"
          alt="Spinning cat"
          class="w-40 h-40 rounded-lg"
        />
      </div>

      
      <audio autoplay>
        <source src="/Sound2.m4a" type="audio/mp4" />
        Your browser does not support the audio element.
      </audio>
    </div>
  </section>
  <Footer />
</template>

<script setup>
import { ref, onMounted } from 'vue'
import { useRouter } from 'vue-router'
import NavBar from '../components/NavBarlogin.vue'
import Footer from '../components/Footer.vue'

const router = useRouter()
const showGif = ref(false)

onMounted(() => {
  showGif.value = true
  const timer = setTimeout(() => {
    router.push('/')
  }, 4000)
  // cleanup
  return () => clearTimeout(timer)
})
</script>

<style scoped>

</style>
