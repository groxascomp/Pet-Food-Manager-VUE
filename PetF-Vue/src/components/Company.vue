<template>
  <div>
    

    <!-- Dog meme GIF (larger) -->
    <div class="flex justify-center my-8">
      <img
        src="/The Dog GIF.gif"
        alt="Funny dog meme"
        class="rounded-lg shadow-lg w-[620px] h-auto"
      />
    </div>

  </div>
</template>

<script setup>
import NavBar from '../components/NavBar.vue'
import Footer from '../components/Footer.vue'
</script>

<style scoped>
/* Optional: force larger size if you prefer CSS instead of Tailwind */
img {
  max-width: 900px;
  height: auto;
}
</style>
