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
      <h1 class="text-3xl font-bold text-gray-800 mb-4">Pet Level Status</h1>
      <p class="text-gray-600 mb-6"></p>
      <br />

     
      <div class="flex items-center justify-center gap-3 mb-6">
        <span class="text-lg font-medium text-gray-700">Food Level:</span>
        <span
          class="w-4 h-4 rounded-full"
          :class="irStatus === 'detected' ? 'bg-green-500' : 'bg-red-500'"
        ></span>
        <span class="text-gray-800 font-semibold">
          {{ irStatus === 'detected' ? 'Sufficient Food Available' : 'Low Level' }}
        </span>
      </div>

      
      <div v-if="irStatus === 'detected'" class="flex justify-center mb-6">
        <img src="/happy-cat.gif" alt="Happy cat" class="w-60 h-60" />
      </div>

     
      <div v-else class="flex flex-col items-center mb-6">
        <img src="/SadCat.gif" alt="Sad cat" class="w-40 h-40 mb-4" />
        <div class="bg-yellow-100 border border-yellow-400 text-yellow-800 px-4 py-3 rounded relative">
          <strong class="font-bold">Notice: </strong>
          <span class="block sm:inline">
            Kindly replenish your food supply to ensure that we are able to
            provide your pet with the appropriate portion of meals each day.
            Maintaining a consistent stock of food helps us safeguard your
            pet’s health and well-being.
          </span>
        </div>
      </div>

      
      <audio ref="audioRef">
        <source src="/Happy.m4a" type="audio/mp4" />
      </audio>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted, watch } from 'vue'

const irStatus = ref('none')
const ESP_IP = 'http://10.58.198.63'
const audioRef = ref(null)
const prevStatus = ref('none')

const fetchStatus = async () => {
  try {
    const res = await fetch(`${ESP_IP}/irStatus`)
    if (!res.ok) throw new Error('Bad response')
    const data = await res.json()
    irStatus.value = data.status
  } catch {
    irStatus.value = 'none'
  }
}

onMounted(() => {
  fetchStatus()
  const interval = setInterval(fetchStatus, 3000)
  onUnmounted(() => clearInterval(interval))
})

// 👇 Play sound whenever status switches to "detected"
watch(irStatus, (newVal) => {
  if (newVal === 'detected' && prevStatus.value !== 'detected' && audioRef.value) {
    audioRef.value.play().catch(err => console.error('Audio play failed:', err))
  }
  prevStatus.value = newVal
})
</script>

<style scoped>

</style>
