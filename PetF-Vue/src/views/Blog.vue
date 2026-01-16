<template>
  <div
    class="h-[684px]"
    style="
      background: linear-gradient(-90deg, rgba(81, 104, 124, 0.0), rgba(56, 73, 111, 0.0)),
                 url('/cat-food-bg.jpg') center/cover no-repeat fixed;
      padding-top: 60px;
    "
  >
    <div
      class="bg-white shadow rounded-lg p-8 max-w-xl mx-auto text-center"
      style="padding-top: 20px;"
    >
      <h1 class="text-3xl font-bold text-gray-800 mb-4">🐾 Pet Facts Blog 🐾</h1>
      <p
        class="text-gray-600 mb-10"
        style="padding-top: 20px; padding-bottom: 20px;"
      >
        Discover fun and quirky facts about pets!
      </p>

      <p v-if="loading" class="text-gray-500">Loading a pet fact...</p>
      <p v-if="error" class="text-red-500">{{ error }}</p>
      <div
        v-if="!loading && !error"
        class="bg-blue-50 border border-blue-200 text-blue-800 px-4 py-3 rounded mb-6"
      >
        <span class="block">{{ petFact }}</span>
      </div>

      <button
        @click="fetchPetFact"
        class="bg-blue-600 hover:bg-blue-700 text-white font-semibold py-2 px-4 rounded transition"
      >
        Get Another Fact
      </button>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'

const petFact = ref('')
const loading = ref(true)
const error = ref('')

const playSound = (type) => {
  let audio
  if (type === 'dog') {
    audio = new Audio('/bark.mp3')
  } else if (type === 'cat') {
    audio = new Audio('/meow-1.mp3')
  }
  if (audio) {
    audio.play().catch(err => console.error('Audio play failed:', err))
  }
}

const fetchPetFact = async () => {
  loading.value = true
  error.value = ''
  try {
    const sources = [
      { type: 'cat', url: 'https://catfact.ninja/fact' },
      { type: 'dog', url: 'https://dogapi.dog/api/v2/facts' }
    ]
    const choice = sources[Math.floor(Math.random() * sources.length)]

    const res = await fetch(choice.url)
    if (!res.ok) throw new Error('Failed to fetch pet fact')
    const data = await res.json()

    if (choice.type === 'cat') {
      petFact.value = '🐱 ' + data.fact
      playSound('cat')
    } else if (choice.type === 'dog') {
      petFact.value = '🐶 ' + data.data[0].attributes.body
      playSound('dog')
    }
  } catch (err) {
    error.value = 'Oops! Could not fetch a pet fact right now.'
  } finally {
    loading.value = false
  }
}

onMounted(() => {
  fetchPetFact()
})
</script>

<style scoped>

</style>
