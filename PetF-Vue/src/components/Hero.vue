<template>
  <section
    id="home"
    class="hero h-[684px]"
    style="
      background: linear-gradient(-90deg, rgba(81, 104, 124, 0.0), rgba(56, 73, 111, 0.0)),
                 url('/cat-food-bg.jpg') center/cover no-repeat fixed;
      padding-bottom: 23px;
    "
  >
    <div class="hero__content container">
      <!-- Updated heading -->
      <h1 class="hero__title text-6xl font-extrabold text-gray-800">
        Hello Fur Parent!
      </h1>

      <p class="hero__subtitle">
        “Your pet misses you—and we’re here to make sure they feel loved,
        cared for, and happy while you’re away.”
      </p>

      <div class="hero__actions">
        <button
          @click="router.push('/about')"
          class="bg-[rgb(13,58,81)] hover:bg-[rgb(83,126,149)] text-white font-bold py-2 px-4 rounded shadow flex items-center"
        >
          Feed Me!
        </button>

        <button
          @click="router.push('/services')"
          class="bg-white text-[rgb(13,58,81)] font-bold py-2 px-4 rounded shadow flex items-center border border-[rgb(13,58,81)] hover:bg-[rgb(83,126,149)] hover:text-white transition-colors"
        >
          Tracker
        </button>
      </div>
    </div>
  </section>
</template>

<script setup>
import { useRouter } from 'vue-router'

const router = useRouter()
</script>

<style scoped>

</style>
